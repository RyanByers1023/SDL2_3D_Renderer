#pragma once
#include "Vec2.h"
#include <vector>
#include <cmath>

class PolygonClipper {
public:
	void Clip(const Triangle2D& triToClip, Polygon2D& newPolygon, const Edge& clipWindowEdge);
	float GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex);
	bool VertexInside(const Edge& clipWindowEdge, const Vec2& currVertex);
	Vec2 FindIntercept(const Edge& clipWindowEdge, const Edge& triEdge);
private:
	const float EPSILON = 1e-6;
	bool IsNearlyEqual(float a, float b) const;
};

