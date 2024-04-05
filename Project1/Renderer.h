#pragma once
#include "Screen.h"
#include "WorldObjects.h"
#include <iostream>


class Renderer {
public:
	//default constructor
	Renderer(int windowWidth, int windowHeight, WorldObjects* worldObjects);
	//destructor
	~Renderer();
	//public methods:
	bool Render(); //render objects to the screen. Returns false if there was an error (no items to render)
private:
	void CalculateNormalVector(const triangle tri);
	bool ShouldRender(const triangle tri);
	Screen* screenPtr;
	ProjectionMatrix* projMatrixPtr;
	WorldObjects* worldObjectsPtr; //use this to store all of the objects and their respective names. names are currently used to differentiate between objects in the game world.
	vec3 normal;
	vec3 cameraLocation;
};
