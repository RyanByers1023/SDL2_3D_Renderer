#pragma once
#include "Screen.h"
#include <numeric>
#include <cmath>

class Line{
public:
	Line(Screen* screenPtr);
	Line(Screen* screenPtr, float x1, float y1, float x2, float y2);
	void Draw();
	void DrawHorizontalLine();
	float x1, x2, y1, y2;
private:	
	Screen* screenPtr;
};