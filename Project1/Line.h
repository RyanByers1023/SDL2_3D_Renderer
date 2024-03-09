#pragma once
#include "Screen.h"
#include <numeric>
#include <cmath>

class Line{
public:
	float length; //length of line
	float angle; //angle of line (in radians)
	Line(Screen& screen, float x1, float y1, float x2, float y2);
	void Draw();
private:
	float x1, x2, y1, y2, dy, dx;
	Screen* screenPtr;
};