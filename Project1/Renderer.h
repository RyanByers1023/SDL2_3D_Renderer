#pragma once
#include "Screen.h"
#include "PrimitiveObject.h"
#include <string>
#include <iostream>
#include <unordered_map>


class Renderer {
public:
	//default constructor
	Renderer(int windowWidth, int windowHeight);
	~Renderer();
	//Renderer(Screen& screen, ProjectionMatrix& projMatrix, std::vector<PrimitiveObject>); //can begin with a premade list of objects if desired
	//public methods:
	void StartRendering();
	bool Render(); //render objects to the screen. Returns false if there was an error (no items to render)
	//public attributes:
	Screen* screenPtr;
	std::unordered_map<std::string, PrimitiveObject> worldObjects; //use this to store all of the objects and their respective names
private:	
	ProjectionMatrix* projMatrixPtr;
};
