#include "Line.h"

Line::Line(Screen &screen, float x1, float y1, float x2, float y2) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->screenPtr = &screen;
}

void Line::Draw() {
    float dx = x2 - x1; // Change in x
    float dy = y2 - y1; // Change in y

    // Calculate the absolute value of dx and dy
    float steps = std::max(abs(dx), abs(dy));

    // Incremental change in x and y per step
    float deltaX = dx / steps;
    float deltaY = dy / steps;

    // Draw each pixel along the line
    for (int i = 0; i <= steps; i++) {
        screenPtr->CreatePixel(round(x1 + i * deltaX), round(y1 + i * deltaY));
    }
}