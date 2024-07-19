#include "PolygonClipper.h"
    //Process overview:
    //the goal is to clip the polygons on the x-axis at screenWidth, and the y-axis at screenHeight. (if needed at all)
    //when clipping is performed, a modification is directly made to the projected 2-D triangle's vertices
    //these vertices will change only for that frame though...
    //when the next frame occurs, the 3-D -> 2-D transformation and will overwrite these changes and the process will begin again
    //Clipping area vertices, assume 1920x1080 resolution: (0, 1080), (1920, 1080), (1920, 0), (0,0)  <--- counter-clockwise order

    //How to determine what side of the window an edge lies?:
    //Eqn: P = (x2 - x1) * (y - y1) - (y2 -y1) * (x - x1)
    //Evaluate this using these rules:
    //P < 0 ---> vertices on right side of line
    //P = 0 ---> vertices on the line
    //P > 0 ---> vertices on the left side of the line  

    //---Process to clip edges---
    //Cases to handle (4)
    //-Both inside ()
    //-First outside, second inside
    //-First inside, second outside
    //-Both outside

    //1. get triangle vertices
    //2. get clipping window (screen space) coordinates
    //3. pick a clipping window edge to begin clipping with
    //4. compare vertices of each edge of the triangle with the clipping plane individually
    //5. save intersections in new list respective to four above relationships
    //6. repeat steps 4 and 5 for all edges of clipping window

//return a list of vertices that should have an edge rendered between them
void PolygonClipper::Clip(const Triangle2D& triToClip, Polygon2D& newPolygon, const Edge& clipWindowEdge){ 
    Vec2 intercept; //store intercept between triangle edge and clipWindowEdge
    Edge triEdge; //store current edge this function is trying to clip

    for(int i = 0; i < 3; ++i){ //loop through all edges of triangle (3)
        //set up vertices vi -> vi+1 that make up the edge I want to check for
        triEdge.v1 = triToClip.vertices[i];
        triEdge.v2 = triToClip.vertices[(i + 1) % 3]; //wrap around to the first vertex on the last iteration to check the last edge

        //Both inside -- keep vertices: second vertex only
        if(VertexInside(clipWindowEdge, triEdge.v1) && VertexInside(clipWindowEdge, triEdge.v2)){ //both inside
            newPolygon.vertices.push_back(triEdge.v2); //keep second vertex
        }
        //First inside, second outside -- keep vertices: intersection w/ clipWindowEdge
        else if(VertexInside(clipWindowEdge, triEdge.v1) && !VertexInside(clipWindowEdge, triEdge.v2)){ //1st inside, 2nd not
            intercept = FindIntercept(clipWindowEdge, triEdge); //find intercept

            //only keep intersection point if it exists
            if (!std::isnan(intercept.x) && !std::isnan(intercept.y)) { //both not invalid (x and y)
                newPolygon.vertices.push_back(intercept); //keep intercept
            }
        }
        //First outside, second inside -- keep vertices: intersection w/ clipWindowEdge + second vertex
        else if(!VertexInside(clipWindowEdge, triEdge.v1) && VertexInside(clipWindowEdge, triEdge.v2)){ //1st outside, 2nd inside
            intercept = FindIntercept(clipWindowEdge, triEdge); //find intercept

            //only keep intersection point if it exists
            if (!std::isnan(intercept.x) && !std::isnan(intercept.y)) { //both not invalid (x and y)
                newPolygon.vertices.push_back(intercept); //keep intercept
            }
            newPolygon.vertices.push_back(triEdge.v2); //keep second vertex
        }
        //If none of these are eval. to true, then the verts are both outside -- do not keep any vertices
    } 
}

float PolygonClipper::GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex){ //Computes cross product between edge v1 -> v2 with respect to currVertex
    //Eqn: P = (x2 - x1) * (y - y1) - (y2 -y1) * (x - x1)

    //extract vertices defining the edge
    Vec2 v1 = clipWindowEdge.v1, v2 = clipWindowEdge.v2;
    return (v2.x - v1.x) * (currVertex.y - v1.y) - (v2.y - v1.y) * (currVertex.x - v1.x);
}

//if clipper vertices are defined counter-clockwise (they will be), then all verticess to the LEFT are inside the clipper boundaries
bool PolygonClipper::VertexInside(const Edge& clipWindowEdge, const Vec2& currVertex){
    return GetEdgeFunctionDet(clipWindowEdge, currVertex) >= 0;
}

Vec2 PolygonClipper::FindIntercept(const Edge& clipWindowEdge, const Edge& triEdge){
    //extract vertices defining all relevant edges
    Vec2 v1 = clipWindowEdge.v1, v2 = clipWindowEdge.v2, v3 = triEdge.v1, v4 = triEdge.v2;

    Vec2 output;

    float denom = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);

    //if (!std::isnan(intersection.x) && !std::isnan(intersection.y)) use this to check for this scenario
    if(IsNearlyEqual(denom, 0.0f)){ //lines are parallel or conincident -- no intersection can exist
        //set output vector to represent this using NaN values
        output.x = std::numeric_limits<float>::quiet_NaN();
        output.y = std::numeric_limits<float>::quiet_NaN();
        return output;
    }

    //x-intercept = ((x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4))
    output.x = ((v1.x * v2.y - v1.y * v2.x) * (v3.x - v4.x) - (v1.x - v2.x) * (v3.x * v4.y - v3.y * v4.x)) / denom;

    //y-intercept = ((x1y2 - y1x2)(y3 -y4) - (y1 - y2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 -x4))
    output.y = ((v1.x * v2.y - v1.y * v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x * v4.y - v3.y * v4.x)) / denom;

    return output;
}


//sometimes denom will not be exactly 0, but so small it can be deemed close enough
bool PolygonClipper::IsNearlyEqual(float a, float b) const {
    return fabs(a - b) < EPSILON;
}
