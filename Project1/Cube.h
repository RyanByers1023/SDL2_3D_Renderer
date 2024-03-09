#pragma once
#include "screen.h"
#include "vertex.h"
#include "Line.h"
#include <vector>

class Cube { //i will eventually create a generic object class that will contain most of these methods as these will be used for more basic shapes than the cube
public:
	//constructor
	Cube(Screen& screen, vec3 position = {0, 0, 0}, float size = 1);
	//public methods
	void Draw();
	vec3 GetPosition();
	void Rotate();
private:
	//private methods
	void CalcCenteroid();
	//private attributes
	Screen* screenPtr;
	mesh cubeMesh;
	vec3 centeroid;
	vec3 position;
	vec3 vertices[8];
};
