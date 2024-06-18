#pragma once
#include "Vec2.h"
#include <vector>

class PolygonClipper {
public:
	void Clip(Triangle2D& triToClip, Polygon2D& newPolygon, const Edge& clipWindowEdge);
	float GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex);
	bool VertexInside(const Edge& clipWindowEdge, const Vec2& currVertex);
	Vec2 FindIntercept(const Edge& clipWindowEdge, const Edge& triEdge);
private:

};
