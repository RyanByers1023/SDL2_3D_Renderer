#pragma once
#include "Screen.h"
#include "WorldObjects.h"
#include "Vec2.h"
#include "RendererHelperFunctions.h"
#include "Shader.h"
#include <vector>
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
	Screen* screenPtr;
	ProjectionMatrix* projMatrixPtr;
	Shader* shaderPtr;
	WorldObjects* worldObjectsPtr; //use this to store all of the objects and their respective names. names are currently used to differentiate between objects in the game world.
	Vec3 normal;
	Vec3 cameraLocation; //this will be its own object at one point or another (playerCamera.cpp or something or another)
};
