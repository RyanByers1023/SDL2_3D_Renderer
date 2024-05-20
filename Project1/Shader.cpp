#include "Shader.h"

Shader::Shader(Screen* screenPtr) {
	this->screenPtr = screenPtr;
}

//in its current state, this rendering process WILL NOT work. Objects that fall outside of the viewing frustrum
//(determined by the camera pos and the 3-D -> 2-D projection matrix transformation inputs) will have their x-coordinates
//(or y-coordinates --- depending on what part of the shape lies outside of the viewing frustrum) increase
//towards +inf. causes instability problems like incredibly large fps drops and visual glitches.
//clipping function NEEDS to be implemented for this engine to work at all at this state in the project

void Shader::ShadeTriangle(const Triangle2D& projTriangle) {
    BoundingBox boundingBox = GetBoundingBox(projTriangle); //check for pixel only within this area

    for(int y = boundingBox.minPoint.y; y < boundingBox.maxPoint.y; y++){ //area to search in y
        for(int x = boundingBox.minPoint.x; x < boundingBox.maxPoint.x; x++){ //area to search in x
            Vec2 currPoint = {x, y}; //create a Vec2 that represents the current point within the boundingbox we are currently checking for intersections with the projected triangle projTriangle
            if(IntersectsTriangle(currPoint, projTriangle)){ //determine if the pixel we are looking at is within or on one of the edges of the triangle. If it is, draw it to the screen
                //Apply shading to pixel (not implemented as of yet)
                //Color pixel (not implemented as of yet)

                //Draw the pixel (add to list of pixels that are to be rendered in screen object)
                Pixel newPixel(screenPtr, x, y); //create the pixel
                newPixel.Draw(); //add to list of pixels to be drawn on screen.show() call (called within Renderer.cpp)
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

    //now we need to clip the bounding box
    ClampBoundingBox(boundingBox);

    return boundingBox;
}

void Shader::ClampBoundingBox(BoundingBox& boundingBox){//process that clamps the boundingBox to be within the screen space, and convert floats to integers for easy iteration through the bounding box
    boundingBox.minPoint.x = std::max(0, static_cast<int>(std::floor(boundingBox.minPoint.x))); //clamp between 0 and the min x val of the boundingBox (if a float, it is rounded down)
    boundingBox.minPoint.y = std::max(0, static_cast<int>(std::floor(boundingBox.minPoint.y))); //clamp between 0 and the min y val of the boundingBox (if a float, it is rounded down)
    boundingBox.maxPoint.x = std::min(screenWidth - 1, static_cast<int>(std::ceil(boundingBox.maxPoint.x))); //clamp between screenWidth - 1 and the max x val of the boundingBox (if a float, it is rounded up)
    boundingBox.maxPoint.y = std::min(screenHeight - 1, static_cast<int>(std::ceil(boundingBox.maxPoint.y))); //clamp between screenHeight - 1 and the max y val of the boundingBox (if a float, it is rounded up)
}

bool Shader::IntersectsTriangle(const Vec2& currPoint, const Triangle2D& projTriangle){ //if all of the below statements equate to true (all cross product operations >= 0) the point intersects projTriangle, therfore we want to draw this point.
    return GetEdgeFunctionValue(currPoint, projTriangle.point[0], projTriangle.point[1]) >= 0 && //edge from p0 to p1
           GetEdgeFunctionValue(currPoint, projTriangle.point[1], projTriangle.point[2]) >= 0 && //edge from p1 to p2
           GetEdgeFunctionValue(currPoint, projTriangle.point[2], projTriangle.point[0]) >= 0;   //edge from p2 to p0
}

float Shader::GetEdgeFunctionValue(const Vec2& currPoint, const Vec2& v0, const Vec2& v1){ //Computes cross product between v0 and v1 with respect to currPoint
    //How to evaluate this functions output:
    //Pos vals fall within the triangle (RENDER)
    //Neg vals fall outside of the triangle (DO NOT RENDER)
    //If evaluates to 0, this point (x, y) falls on the edge exactly. (RENDER)

    //calculate the cross product of two inputted vectors with respect to currPoint:
    float edgeFunctionValue = (v1.x - v0.y) * (currPoint.y - v0.y) - (v1.y - v0.y) * (currPoint.x - v0.x);
    return edgeFunctionValue; //return value for evaluation in IntersectsTriangle
}

bool Shader::IsWithinScreenBounds(BoundingBox boundingBox){
    boundingBox.minPoint.x = std::max(0, boundingBox.minPoint.x);
    boundingBox.minPoint.y = std::max(0, boundingBox.minPoint.y);
    boundingBox.maxPoint.x = std::min(screenWidth - 1, boundingBox.maxPoint.x);
    boundingBox.maxPoint.y = std::min(screenHeight - 1, boundingBox.maxPoint.y);
}

