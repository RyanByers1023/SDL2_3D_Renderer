#pragma once
#include "Vec3.h"
#include <vector>

class Vec2 {
public:
	//default constructor
	Vec2() : x(0.0f), y(0.0f) {};

	//constructor with float parameters
	Vec2(float x, float y) : x(x), y(y) {};

	//contructor with int parameters
	Vec2(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {};

	//assignment operator to assign from Vec3
	Vec2& operator=(const Vec3& otherVector);

	//public member variables
	float x;
	float y;
};

struct Edge {
	Vec2 v1;
	Vec2 v2;
};

struct Triangle2D {
	Vec2 vertices[3];
};

struct Polygon2D{
	std::vector<Vec2> vertices;
};