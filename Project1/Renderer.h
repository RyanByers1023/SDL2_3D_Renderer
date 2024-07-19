#pragma once
#include "Screen.h"
#include "WorldObjects.h"
#include "Vec2.h"
#include "RendererHelperFunctions.h"
#include "Shader.h"
#include "PolygonClipper.h"
#include <vector>
#include <iostream>


class Renderer {
public:
	//default constructor
	Renderer(int windowWidth, int windowHeight, WorldObjects* worldObjects);

	//destructor
	~Renderer();

	//render objects to the screen. Returns false if there was an error (no items to render)
	bool Render(); 
private:
	//private member variables
	Screen* screenPtr;
	ProjectionMatrix* projMatrixPtr;
	Shader* shaderPtr;
	WorldObjects* worldObjectsPtr; //used to store all objects in game world and respective names.
	PolygonClipper* clipperPtr;
	std::vector<Polygon2D> polygonList;
	Vec3 normal;
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
	void GetClippedPolygons();

	//draw polygons to the screen
	void DrawPolygons();
};
