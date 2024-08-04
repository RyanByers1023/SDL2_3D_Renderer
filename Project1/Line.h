#pragma once
#include "Screen.h"
#include "Vec2.h"
#include <numeric>
#include <cmath>

class Line{
public:
	//if no coordinates are given, set all to origin
	Line(Screen* screenPtr) : screenPtr(screenPtr), line.v1.x(0.0f), line.v1.y(0.0f), line.v2.x(0.0f), line.v2.y(0.0f) {};
	//floats given, store as edge
	Line(Screen* screenPtr, const float& x1, const float& y1, const float& x2, const float& y2) : screenPtr(screenPtr), line.v1.x(x1), line.v1.y(y1), line.v2.x(x2), line..v2.y(y2) {};
	//2D vertices (Vec2) given, store as edge
	Line(Screen* screenPtr, const Vec2& v1, const Vec2& v2) : screenPtr(screenPtr), line.v1(v1), line.v2(v2) {};
	//edge given, store as is
	Line(Screen* screenPtr, const Edge& line) : screenPtr(screenPtr), line(line) {};
	void Draw();
	Edge line;
private:	
	Screen* screenPtr;
};