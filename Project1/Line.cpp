#include "Line.h"

Line::Line(Screen* screenPtr) {
	this->line.v1.x = 0.0f;
    this->line.v2.x = 0.0f;
    this->line.v1.y = 0.0f;
    this->line.v2.y = 0.0f;
    this->screenPtr = screenPtr;
}

Line::Line(Screen* screenPtr, const float& x1, const float& y1, const float& x2, const float& y2) {
	this->line.v1.x = x1;
    this->line.v2.x = x2;
    this->line.v1.y = y1;
    this->line.v2.y = y2;
	this->screenPtr = screenPtr;
}

Line::Line(Screen* screenPtr, const Vec2& v1, const Vec2& v2){
    this->line.v1.x = v1.x;
    this->line.v2.x = v2.x;
    this->line.v1.y = v1.y;
    this->line.v2.y = v2.y;
    this->screenPtr = screenPtr;
}

Line::Line(Screen* screenPtr, const Edge& line){
    this->line = line;
    this->screenPtr = screenPtr;
}

void Line::Draw() {
    float dx = x2 - x1; // Change in x
    float dy = y2 - y1; // Change in y

    // Calculate the absolute value of dx and dy, take the largest value
    float steps = std::max(abs(dx), abs(dy));

    if (steps == 0) { //there is no change in x or y. this is a single point
        screenPtr->CreatePixel(round(x1), round(y1)); // Draw a single pixel
        return; // End the function after drawing the pixel
    }

    // Incremental change in x and y per step
    float deltaX = dx / steps; //steps != 0
    float deltaY = dy / steps; //steps != 0

    // Draw each pixel along the line
    for (int i = 0; i <= steps; i++) {
        screenPtr->CreatePixel(round(x1 + i * deltaX), round(y1 + i * deltaY));
    }
}