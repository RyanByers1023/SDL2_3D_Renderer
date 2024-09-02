#pragma once
#include "Screen.h"
#include "vec2.h"
#include "vec3.h"
#include "Material.h"
#include "Light.h"
#include <map>
#include <cmath>
#include <algorithm>

struct BoundingBox { //used for determing the area we need to check for intersections
	Vec2 minPoint; // -- > top-left corner of bounding box
	Vec2 maxPoint; // -- > bottom-right corner of bounding box
};

class Shader {
public:
	//default constructor
	Shader(std::shared_ptr<Screen> screenPtr) : screenPtr(screenPtr) {}
	void ShadePolygon(const Polygon2D& polygon);
	Vec3 CalculateVertexColor(const Vec3& vertexPos, const Vec3& vertexNormal, const Light& light, const Vec3& cameraPos, const Material& material);
private:
	BoundingBox GetBoundingBox(const Polygon2D& polygon);
	void ClampBoundingBox(BoundingBox& boundingBox);
	bool IntersectsPolygon(const Vec2& currPoint, const Polygon2D& polygon);
	float GetEdgeFunctionDet(const Vec2& currPoint, const Vec2& v0, const Vec2& v1);
	Vec3 ClampColor(const Vec3& color);
	std::shared_ptr<Screen> screenPtr;
};
