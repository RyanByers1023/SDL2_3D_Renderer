#pragma once
#include "Screen.h"
#include "WorldObjects.h"
#include "Vec2.h"
#include "RendererHelperFunctions.h"
#include "Shader.h"
#include "PolygonClipper.h"
#include <vector>
#include <iostream>
#include <memory>


class Renderer {
public:
	//default constructor
	Renderer(int windowWidth, int windowHeight);

	//draw objects to the screen
	bool Render(std::shared_ptr<WorldObjects> worldObjectsPtr); 
private:
	//private member variables
	std::shared_ptr<Screen> screenPtr;
	std::unique_ptr<ProjectionMatrix> projMatrixPtr;
	Shader shader;
	PolygonClipper clipper;
	Vec3 cameraLocation;

	//screen space bounding box member variables
	Edge boundingEdgeLeft;
	Edge boundingEdgeRight;
	Edge boundingEdgeTop;
	Edge boundingEdgeBottom;

	//set screen space bounding box
	void SetScreenSpaceBoundaries();

	Vec2 GetScreenSpaceVertex(const Vec3& vertex, const Vec3& cameraLocation, const float& width, const float& height) const;

	//clip triangles from mesh
	void GetClippedPolygons(std::vector<Polygon2D>& polygonList, std::shared_ptr<WorldObjects> worldObjectsPtr);

	Polygon2D PerformClipping(const Polygon2D& projectedTriangle);

	//draw polygons to the screen
	void DrawPolygons(const std::vector<Polygon2D>& polygonList);
};
