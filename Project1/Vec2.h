#pragma once
#include "Vec3.h"

class Vec2 {
public:
	Vec2();
	Vec2(float x, float y);
	Vec2(int x, int y);
	Vec2& operator=(const Vec3& otherVector);
	float x;
	float y;
};

struct Triangle2D {
	Vec2 point[3];
};