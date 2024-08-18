#pragma once
#include "Vec2.h"
#include <vector>
#include <cmath>
#include <iostream>

class PolygonClipper {
public:
	Polygon2D Clip(const Polygon2D& inputPolygon, const Edge& clipWindowEdge) const;
	float GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex) const;
	bool VertexInside(const Edge& clipWindowEdge, const Vec2& currVertex) const;
	Vec2 FindIntercept(const Edge& clipWindowEdge, const Edge& triEdge) const;
};

