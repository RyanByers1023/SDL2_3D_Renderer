#pragma once
#include "Vec2.h"
#include <vector>

void ClipVertices(const Triangle2D& triToClip, Polygon2D& newPolygon, const Edge& clipWindowEdge); //newPolygon represents the output of this function, this is the object we will ultimately render

float GetEdgeFunctionDet(const Edge& clipWindowEdge, const Vec2& currVertex);
bool VertexInside(float determinant, const Edge& clipWindowEdge, const Vec2& currVertex);
Vec2 FindIntercept(const Edge& clipWindowEdge, const Edge& triEdge);