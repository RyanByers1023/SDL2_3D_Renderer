#include "Line.h"

void Line::Draw() {
    float dx = line.v2.x - line.v1.x; // Change in x
    float dy = line.v2.y - line.v1.y; // Change in y

    // Calculate the absolute value of dx and dy, take the largest value
    float steps = std::max(abs(dx), abs(dy));

    if (steps == 0) { //there is no change in x or y. this is a single point
        screenPtr->CreatePixel(round(line.v1.x), round(line.v1.y)); // Draw a single pixel
        return; // End the function after drawing the pixel
    }

    // Incremental change in x and y per step
    float deltaX = dx / steps; //steps != 0
    float deltaY = dy / steps; //steps != 0

    // Draw each pixel along the line
    for (int i = 0; i <= steps; i++) {
        screenPtr->CreatePixel(round(line.v1.x + i * deltaX), round(line.v1.y + i * deltaY));
    }
}