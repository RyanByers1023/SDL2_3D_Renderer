#pragma once
#include "Vec2.h"
#include <vector>
#include <cmath>
#include <iostream>

class PolygonClipper {
public:
	Polygon2D Clip(const Polygon2D& inputPolygon, const Edge& clipWindowEdge);
	float GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex);
	bool VertexInside(const Edge& clipWindowEdge, const Vec2& currVertex);
	Vec2 FindIntercept(const Edge& clipWindowEdge, const Edge& triEdge);
};

