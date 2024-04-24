#include "Shader.h"

Shader::Shader(Screen* screenPtr) {
	this->screenPtr = screenPtr;
	linePtr = new Line(screenPtr);
}

Shader::~Shader(){
	delete this->linePtr;
}

//in its current state, this rendering process WILL NOT work. Objects that fall outside of the viewing frustrum
//(determined by the camera pos and the projection matrix inputs) will have their x-coordinates
//(or y-coordinates --- depending on what part of the shape lies outside of the viewing frustrum) increase
//towards +inf. causes instability problems like incredibly large fps drops and visual glitches.
//clipping function NEEDS to be implemented for this engine to work at all at this state in the project

void Shader::ShadeTriangle(const Triangle2D& projTriangle) {
    BoundingBox boundingBox = GetBoundingBox(projTriangle); //check for pixel only within this area
    for(int y = boundingBox.minPoint.y; y < boundingBox.maxPoint.y; ++y){ //area to search in y
        for(int x = boundingBox.minPoint.x; x < boudingBox.maxPoint.x; ++x){ //area to search in x
            if(IsInsideTriangle(x, y, projTriangle)){ //determine if the pixel we are looking at (within boundingBox) is within or on the triangle. If it is, draw it to the screen
                //Apply shading to pixel (not implemented as of yet)
                //Color pixel (not implemented as of yet)
                //drawPixel(x, y); (need to implement this)
            }
        }
    }
}

//the below function is not required for the rasterization process... but significantly improves performance. Caps the number of pixels that are required to be checked for itersection with the triangle's edges
BoundingBox Shader::GetBoundingBox(const Triangle2d& projTriangle){
    BoundingBox boundingBox;

    //calculate the minimum x coordinate (closest to origin) and minimum y coordinate
    float minX = std::min(projTriangle.point[0].x, projTriangle.point[1].x projTriangle.point[2].x);
    float minY = std::min(projTriangle.point[0].y, projTriangle.point[1].y projTriangle.point[2].y);
    float maxX = std::max(projTriangle.point[0].x, projTriangle.point[1].x projTriangle.point[2].x);
    float maxY = std::max(projTriangle.point[0].y, projTriangle.point[1].y projTriangle.point[2].y);

    //store these values in our boundingBox object for later use
    boundingBox.minPoint.x = minX;
    boundingBox.minPoint.y = minY;
    boundingBox.maxPoint.x = maxX;
    boundingBox.maxPoint.y = maxY;

    return boundingBox;
}

bool Shader::IsInsideTriangle(const Vec2& pointToRender, const Triangle2D& projTriangle){ //if all of the below statements equate to true (all cross product operations >= 0 --- meaning pointToRender is within projTriangle) we want to draw this point.
    return GetEdgeFunctionValue(pointToRender, projTriangle.point[0], projTriangle.point[1]) >= 0 && //edge from p0 to p1
           GetEdgeFunctionValue(pointToRender, projTriangle.point[1], projTriangle.point[2]) >= 0 && //edge from p1 to p2
           GetEdgeFunctionValue(pointToRender, projTriangle.point[2], projTriangle.point[0]) >= 0;   //edge from p2 to p0
}

 float Shader::GetEdgeFunctionValue(const Vec2& pointToRender, const Vec2& v0, const Vec2& v1){ //Computes cross product between v0 and v1 with respect to pointToRender (the vertices that define this particular edge).
    //Pos vals fall within the triangle, negative vals fall on the outside.
    //If evaluates to 0, this point (x, y) falls on the edge exactly.
    //find the cross product of two inputted vectors with respect to pointToRender:
    float edgeFunctionValue = (v1.x - v0.y) * (pointToRender.y * v0.y) - (v1.y - v0.y) * (pointToRender.x - v0.x);
    return edgeFunctionValue;
}

