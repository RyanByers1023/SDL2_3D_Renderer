#pragma once
#include "Screen.h"
#include "Vec2.h"
#include "Line.h"

class Shader {
public:
	Shader(Screen* screenPtr);
	~Shader();
	void FillTriangle(const Triangle2D& projTriangle);
private:
	Screen* screenPtr;
	Line* linePtr;
};
