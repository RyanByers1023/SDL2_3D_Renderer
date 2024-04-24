#include "Shader.h"

struct BoundingBox{ //used for determing the area we need to check for intersections
    Vec2 minPoint; // -- > top-left corner of bounding box
    Vec2 maxPoint; // -- > bottom-right corner of bounding box
}

Shader::Shader(Screen* screenPtr) {
	this->screenPtr = screenPtr;
	linePtr = new Line(screenPtr);
}

Shader::~Shader(){
	delete this->linePtr;
}

void Shader::FillTriangle(const Triangle2D& projTriangle) {
    BoundingBox boundingBox = GetBoundingBox(projTriangle);
}

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
    return GetEdgeFunctionValue(pointToRender, projTriangle.point[0], projTriangle.point[1]) >= 0 &&
           GetEdgeFunctionValue(pointToRender, projTriangle.point[1], projTriangle.point[2]) >= 0 &&
           GetEdgeFunctionValue(pointToRender, projTriangle.point[2], projTriangle.point[0]) >= 0;
}

 float Shader::GetEdgeFunctionValue(const Vec2& pointToRender, const Vec2& v0, const Vec2& v1){ //Computes cross product between v0 and v1 with respect to pointToRender (the vertices that define this particular edge).
    //Pos vals fall within the triangle, negative vals fall on the outside.
    //If evaluates to 0, this point (x, y) falls on the edge exactly.
    //find the cross product of two inputted vectors with respect to pointToRender:
    float edgeFunctionValue = (v1.x - v0.y) * (pointToRender.y * v0.y) - (v1.y - v0.y) * (pointToRender.x - v0.x);
    return edgeFunctionValue;
}

