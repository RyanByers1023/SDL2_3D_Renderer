#pragma once
#include "Screen.h"
#include "Vec2.h"
#include <cmath>

class Shader {
public:
	Shader(Screen* screenPtr);
	void ShadePolygon(const Polygon2D& polygon);
private:
	Screen* screenPtr;
};
