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
	Renderer(const int windowWidth, const int windowHeight);

	//render objects to the screen. Returns false if there was an error (no items to render)
	bool Render(std::unique_ptr<WorldObjects>& worldObjectsPtr);
private:
	//private member variables
	std::unique_ptr<Screen> screenPtr;
	std::unique_ptr<ProjectionMatrix> projMatrixPtr;
	std::unique_ptr<PolygonClipper> clipperPtr;
	Vec3 cameraLocation;

	//screen space bounding box member variables
	Edge boundingEdgeLeft;
	Edge boundingEdgeRight;
	Edge boundingEdgeTop;
	Edge boundingEdgeBottom;

	//set screen space bounding box
	void SetScreenSpaceBoundaries();

	Vec2 GetScreenSpaceVertex(const Vec3& vertex, const Vec3& cameraLocation, const float width, const float height) const;

	void GetAllNormals(std::unique_ptr<WorldObjects>& worldObjectsPtr) const;

	void GetAllFaceNormals(std::unique_ptr<WorldObjects>& worldObjectsPtr) const;

	void GetAllVertexNormals(std::unique_ptr<WorldObjects>& worldObjectsPtr) const;

	void StoreVertexNormals(mesh& triangleMesh) const;

	GetProjectedTriangles(const std::unique_ptr<WorldObjects>& worldObjectsPtr, std::unique_ptr<Polygon2D>& polygonList) const;

	//clip triangles from mesh
	void GetClippedPolygons(std::vector<Polygon2D>& polygonList) const;

	//project a 3-D triangle to 2-space
	Polygon2D ProjectTriangle(const Triangle3D& tri3D) const;

	Polygon2D PerformClipping(const Polygon2D& projectedTriangle) const;

	//draw polygons to the screen
	void DrawPolygons(const std::vector<Polygon2D>& polygonList);
};
