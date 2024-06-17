#pragma once
#include "Screen.h"
#include "Vec2.h"
#include <numeric>
#include <cmath>

class Line{
public:
	//if no coordinates are given, set all to origin
	Line(Screen* screenPtr);
	//floats given, store as edge
	Line(Screen* screenPtr, const float& x1, const float& y1, const float& x2, const float& y2);
	//2D vertices (Vec2) given, store as edge
	Line(Screen* screenPtr, const Vec2& v1, const Vec2& v2);
	//edge given, store as is
	Line(Screen* screenPtr, const Edge& line);
	void Draw();
	Edge line;
private:	
	Screen* screenPtr;
};