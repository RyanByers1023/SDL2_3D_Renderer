#include "PolygonClipper.h"

//return a list of vertices that should have an edge rendered between them
Polygon2D PolygonClipper::Clip(const Polygon2D& inputPolygon, const Edge& clipWindowEdge) const{ 
    Vec2 intercept; //store intercept between triangle edge and clipWindowEdge
    Edge polyEdge; //store current edge this function is trying to clip
    Polygon2D clippedPolygon; //store clipped edges, will build up throughout 4 (# num of clipEdges) iterations of this function

    int numvertices = inputPolygon.vertices.size();

    for(int i = 0; i < numvertices; ++i){ //loop through all edges of polygon

        //obtain vertices, store in polyEdge
        polyEdge.v1 = inputPolygon.vertices[i];
        polyEdge.v2 = inputPolygon.vertices[(i + 1) % numvertices]; //wrap around to the first vertex on the last iteration to check the last edge

        //Both inside -- keep vertices: second vertex only
        if(VertexInside(clipWindowEdge, polyEdge.v1) && VertexInside(clipWindowEdge, polyEdge.v2)){ //both inside
            clippedPolygon.vertices.push_back(polyEdge.v2); //store second vertex
        }

        //First inside, second outside -- keep vertices: intersection w/ clipWindowEdge
        else if(VertexInside(clipWindowEdge, polyEdge.v1) && !VertexInside(clipWindowEdge, polyEdge.v2)){ //1st inside, 2nd not
            intercept = FindIntercept(clipWindowEdge, polyEdge); //find intercept

            clippedPolygon.vertices.push_back(intercept); //store intercept
        }

        //First outside, second inside -- keep vertices: intersection w/ clipWindowEdge + second vertex
        else if(!VertexInside(clipWindowEdge, polyEdge.v1) && VertexInside(clipWindowEdge, polyEdge.v2)){ //1st outside, 2nd inside
            intercept = FindIntercept(clipWindowEdge, polyEdge); //find intercept
            
            clippedPolygon.vertices.push_back(intercept); //store intercept
            clippedPolygon.vertices.push_back(polyEdge.v2); //store second vertex  
        }
        //If none of these are eval. to true, then the verts are both outside -- do not keep any vertices
    }
    return clippedPolygon;
}

//if clipper vertices are defined counter-clockwise (they will be), then all vertices to the LEFT are inside the clipper boundaries
bool PolygonClipper::VertexInside(const Edge& clipWindowEdge, const Vec2& currVertex) const{
    return GetEdgeFunctionDet(clipWindowEdge, currVertex) <= 0; //note: this currently only returns true when vertices are to the right (edge function >= 0); possible problem with clip window edge order being clockwise instead of counter-clockwise?
}

float PolygonClipper::GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex) const{ //Computes cross product between edge v1 -> v2 with respect to currVertex
    //Eqn: P = (x2 - x1) * (y - y1) - (y2 -y1) * (x - x1)

    //extract vertices defining the clipping edge
    Vec2 v1 = clipWindowEdge.v1, v2 = clipWindowEdge.v2;
    //compute the edge function:
    return (v2.x - v1.x) * (currVertex.y - v1.y) - (v2.y - v1.y) * (currVertex.x - v1.x);
}


Vec2 PolygonClipper::FindIntercept(const Edge& clipWindowEdge, const Edge& polyEdge) const{
    //extract vertices defining edges of clip boundary (v1 and v2) and triangle edge (v3 and v4)
    Vec2 v1 = clipWindowEdge.v1, v2 = clipWindowEdge.v2, v3 = polyEdge.v1, v4 = polyEdge.v2;

    Vec2 intercept;

    //pre-calculate denominator of intercept eqn:
    float denom = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);

    //x-intercept = (x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4) / denom
    intercept.x = ((v1.x * v2.y - v1.y * v2.x) * (v3.x - v4.x) - (v1.x - v2.x) * (v3.x * v4.y - v3.y * v4.x)) / denom;

    //y-intercept = (x1y2 - y1x2)(y3 -y4) - (y1 - y2)(x3y4 - y3x4) / denom
    intercept.y = ((v1.x * v2.y - v1.y * v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x * v4.y - v3.y * v4.x)) / denom;

    //return intercept
    return intercept;
}

//Process overview:
//the goal is to clip the polygons on the x-axis at screenWidth, and the y-axis at screenHeight.
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
//-Both inside
//-First outside, second inside
//-First inside, second outside
//-Both outside

//1. get triangle vertices
//2. get clipping window (screen space) coordinates
//3. pick a clipping window edge to begin clipping with
//4. compare vertices of each edge of the triangle with the clipping plane individually
//5. save intersections in new list respective to four above relationships
//6. repeat steps 4 and 5 for all edges of clipping window

