#include "Shader.h"

Shader::Shader(Screen* screenPtr) {
	this->screenPtr = screenPtr;
	linePtr = new Line(screenPtr);
}

Shader::~Shader(){
	delete this->linePtr;
}

void Shader::FillTriangle(const Triangle2D& projTriangle) {
    Vec2 p1, p2, p3;
    p1 = projTriangle.point[0]; p2 = projTriangle.point[1]; p3 = projTriangle.point[2];

    //find triangle bounds
    int minX = std::min({ p1.x, p2.x, p3.x });
    int maxX = std::max({ p1.x, p2.x, p3.x });
    int minY = std::min({ p1.y, p2.y, p3.y });
    int maxY = std::max({ p1.y, p2.y, p3.y });

    //iterate over each scanline
    for (int y = minY; y <= maxY; ++y) {
        linePtr->y1 = y;
        //initialize intersection points
        int x1 = INT_MAX, x2 = INT_MIN;

        //find intersection points with each edge
        if ((y - p1.y) * (p2.x - p1.x) - (p2.y - p1.y) * (p1.x - x1) > 0)
            x1 = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
        if ((y - p1.y) * (p3.x - p1.x) - (p3.y - p1.y) * (p1.x - x1) > 0)
            x1 = p1.x + (y - p1.y) * (p3.x - p1.x) / (p3.y - p1.y);
        if ((y - p2.y) * (p3.x - p2.x) - (p3.y - p2.y) * (p2.x - x2) < 0)
            x2 = p2.x + (y - p2.y) * (p3.x - p2.x) / (p3.y - p2.y);
        if ((y - p2.y) * (p1.x - p2.x) - (p1.y - p2.y) * (p2.x - x2) < 0)
            x2 = p2.x + (y - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);
        if ((y - p3.y) * (p1.x - p3.x) - (p1.y - p3.y) * (p3.x - x2) > 0)
            x2 = p3.x + (y - p3.y) * (p1.x - p3.x) / (p1.y - p3.y);
        if ((y - p3.y) * (p2.x - p3.x) - (p2.y - p3.y) * (p3.x - x2) > 0)
            x2 = p3.x + (y - p3.y) * (p2.x - p3.x) / (p2.y - p3.y);

        //draw horizontal line between intersection points
        if (x1 <= x2) {
            linePtr->x1 = x1; linePtr->x2 = x2; linePtr->y1 = y;
            linePtr->DrawHorizontalLine();
        }
    }
}

