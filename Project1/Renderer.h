#pragma once
#include "Screen.h"
#include "PrimitiveObject.h"


class Renderer {
public:
	//default constructor
	Renderer(Screen* screenPtr, ProjectionMatrix& projMatrix);
	//Renderer(Screen& screen, ProjectionMatrix& projMatrix, std::vector<PrimitiveObject>); //can begin with a premade list of objects if desired
	//public methods:
	void Render(); //render objects to the screen
private:
	Screen* screenPtr;
	ProjectionMatrix projMatrix;
	std::vector<PrimitiveObject> worldObjects;
};
