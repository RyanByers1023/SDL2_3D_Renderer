#pragma once
#include "Screen.h"
#include "PrimitiveObject.h"
#include "InputHandler.h"
#include "LinearTransformations.h"
#include "Time.h"
#include <string>
#include <iostream>
#include <unordered_map>


class Renderer {
public:
	//default constructor
	Renderer(int windowWidth, int windowHeight);
	//destructor
	~Renderer();
	//public methods:
	void StartRendering();
	bool Render(); //render objects to the screen. Returns false if there was an error (no items to render)
	//public attributes:
	Screen* screenPtr;
	std::unordered_map<std::string, PrimitiveObject> worldObjects; //use this to store all of the objects and their respective names. names are currently used to differentiate between objects in the game world.
private:	
	ProjectionMatrix* projMatrixPtr;
	InputHandler* inputHandlerPtr;
	Time* timePtr;
};
