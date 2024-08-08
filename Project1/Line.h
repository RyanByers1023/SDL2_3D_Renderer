#pragma once
#include "Screen.h"
#include "Vec2.h"
#include <numeric>
#include <cmath>

class Line{
public:
	//if no coordinates are given, set all to origin
	Line(Screen* screenPtr) : screenPtr(screenPtr), line(Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f)) {}
	//floats given, store as edge
	Line(Screen* screenPtr, const float& x1, const float& y1, const float& x2, const float& y2) : screenPtr(screenPtr), line(Vec2(x1, y1), Vec2(x2, y2)) {}
	//2D vertices (Vec2) given, store as edge
	Line(Screen* screenPtr, const Vec2& v1, const Vec2& v2) : screenPtr(screenPtr), line(v1, v2) {}
	//edge given, store as is
	Line(Screen* screenPtr, const Edge& line) : screenPtr(screenPtr), line(line) {};

	void Draw();

	Edge line;
private:	
	Screen* screenPtr;
};