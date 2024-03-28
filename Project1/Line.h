#pragma once
#include "Screen.h"
#include <numeric>
#include <cmath>

class Line{
public:
	Line(Screen& screen, float x1, float y1, float x2, float y2);
	void Draw();
private:
	float x1, x2, y1, y2;
	Screen* screenPtr;
};