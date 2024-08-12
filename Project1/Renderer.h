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

	//render objects to the screen. Returns false if there was an error (no items to render)
	bool Render(); 

	std::shared_ptr<WorldObjects> worldObjectsPtr; //used to store all objects in game world and respective names.
private:
	//private member variables
	std::shared_ptr<Screen> screenPtr;
	std::shared_ptr<ProjectionMatrix> projMatrixPtr;
	std::shared_ptr<Shader> shaderPtr;

	std::shared_ptr<PolygonClipper> clipperPtr;
	Vec3 cameraLocation;

	//screen space bounding box member variables
	Edge boundingEdgeLeft;
	Edge boundingEdgeRight;
	Edge boundingEdgeTop;
	Edge boundingEdgeBottom;

	//set screen space bounding box
	void SetScreenSpaceBoundaries();

	Vec2 GetScreenSpaceVertex(const Vec3& vertex, const Vec3& cameraLocation, const float& width, const float& height) const;

	//obtain all relevant normals needed for culling and shading
	void GetAllNormals();

	//get all face normals for objects in 3-space
	void GetAllFaceNormals();

	//get all vertex normals for objects in 3-space
	void GetAllVertexNormals();

	void StoreVertexNormals(mesh& triangleMesh);

	//Project 3-D triangles to 2-space
	Polygon2D ProjectTriangle(const Triangle3D& tri3D);

	//clip triangles from mesh
	void GetClippedPolygons(std::vector<Polygon2D>& polygonList);

	Polygon2D PerformClipping(const Polygon2D& projectedTriangle);

	//draw polygons to the screen
	void DrawPolygons(const std::vector<Polygon2D>& polygonList);
};
