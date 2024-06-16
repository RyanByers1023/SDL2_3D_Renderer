#pragma once
#include "Screen.h"
#include "Vec2.h"
#include <cmath>

struct BoundingBox{ //used for determing the area we need to check for intersections
    Vec2 minPoint; // -- > top-left corner of bounding box
    Vec2 maxPoint; // -- > bottom-right corner of bounding box
}

class Shader {
public:
	Shader(Screen* screenPtr);
	void ShadePolygon(const Polygon2D& polygon);
private:
	BoundingBox GetBoundingBox(const Triangle2d& projTriangle);
	void ClampBoundingBox(BoundingBox& boundingBox);
	bool IntersectsTriangle(const Vec2& pointToCheck, const Triangle2D& projTriangle);
	float GetEdgeFunctionDet(const Vec2& pointToRender, const Vec2& v0, const Vec2& v1);
	Screen* screenPtr;
};
