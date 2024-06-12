#include "PolygonClipper.h"
    //Process overview:

    //the goal is to clip the polygons on the x-axis at screenWidth, and the y-axis at screenHeight. (if needed at all)
    //when clipping is performed, a modification is directly made to the projected 2-D triangle's vertices
    //Clipping area vertices, assume 1920x1080 resolution: (0, 1080), (1920, 1080), (1920, 0), (0,0)  <--- counter-clockwise order

    //How to determine what side of the window an edge lies?:
    //Eqn: P = (x2 - x1) * (y - y1) - (y2 -y1) * (x - x1)
    //Evaluate this using these rules:
    //P < 0 ---> point on right side of line
    //P = 0 ---> point on the line
    //P > 0 ---> point on the left side of the line

    //if clipper vertices are defined counter-clockwise (like above), then all points to the LEFT are inside the clipper boundaries

    //---Finding intersection of two edges---
    

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

float GetEdgeFunctionDet(const Vec2& v1, const Vec2& v2, const Vec2& currPoint){ //Computes cross product between edge v1 -> v2 with respect to currPoint
    //Eqn: P = (x2 - x1) * (y - y1) - (y2 -y1) * (x - x1)
    return (v2.x - v1.x) * (currPoint.y - v1.y) - (v2.y - v1.y) * (currPoint.x - v1.x);
}

bool AnalyzeEdgeFunctionDet(float determinant, const Vec2& v1, const Vec2& v2, const Vec2& currPoint){
    return GetEdgeFunctionDet(currPoint, v1, v2) >= 0;
}

//Assume clip boundary = v1 -> v2 and polygon edge = v3 -> v4
//v1 = (x1, y1), v2 = (x2, y2), v3 = (x3, y3), v4 = (x4, y4) 

float FindXIntercept(const Vec2& v1, const Vec2& v2, const Vec2& v3, const Vec2& v4){
    //x-intercept = ((x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4))

    return ((v1.x * v2.y) - (v1.y * v2.x) * (v3.x - v4.x) - (v1.x - v2.x) * (v3.x * v4.y) - (v3.y * v4.x)) / 
           ((v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x));
}

float FindYIntercept(){
    //y-intercept = ((x1y2 - y1x2)(y3 -y4) - (y1 - y2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 -x4))

    return ((v1.x * v2.y) - (v1.y * v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x * v4.y) - (v3.y * v4.x))/
           ((v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x));
}