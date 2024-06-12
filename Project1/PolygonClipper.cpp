#include "PolygonClipper.h"

bool Inside(int screenWidth, int screenHeight, Triangle2D& triangle){
    //the goal is to clip the polygons on the x-axis at screenWidth, and the y-axis at screenHeight. (if needed at all)
    //when clipping is performed, a modification is directly made to the projected 2-D triangle's vertices
    //Clipping area vertices, assume 1920x1080 resolution: (0, 1080), (1920, 1080), (1920, 0), (0,0)  <--- counter-clockwise order

    //---Process to clip edges---
    //Cases to handle (4)
    //-Both inside ()
    //-First outside, second inside
    //-First inside, second outside
    //-Both outside

    //How to determine this?:
    //Eqn: P = (x2 - x1) * (y - y1) - (y2 -y1) * (x - x1)
    //Evaluate this using these rules:
    //P < 0 ---> point on right side of line
    //P = 0 ---> point on the line
    //P > 0 ---> point on the left side of the line

    //if clipper vertices are defined counter-clockwise (like above), then all points to the LEFT are inside the clipper boundaries

    //---Finding intersection of two edges---
    //Assume clip boundary = v1 -> v2 and polygon edge = v3 -> v4
    //v1 = (x1, y1), v2 = (x2, y2), v3 = (x3, y3), v4 = (x4, y4) 
    //x-intercept = ((x1y2 - y1x2)(x3 - x4) - (x1 - x2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4))
    //y-intercept = ((x1y2 - y1x2)(y3 -y4) - (y1 - y2)(x3y4 - y3x4)) / ((x1 - x2)(y3 - y4) - (y1 - y2)(x3 -x4))
}