#include "Line.h"

Line::Line(Screen* screenPtr) {
    this->x1 = 0.0f;
    this->x2 = 0.0f;
    this->y1 = 0.0f;
    this->y2 = 0.0f;
    this->screenPtr = screenPtr;
}

Line::Line(Screen* screenPtr, float x1, float y1, float x2, float y2) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
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

void Line::DrawHorizontalLine() { //uses y1 as the vertical coordinate
    for (int x = this->x1; x < this->x2; ++x) { //WRONG x2 is going to +inf
        screenPtr->CreatePixel(round(x), round(y1));
    }
}