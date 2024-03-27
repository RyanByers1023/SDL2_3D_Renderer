#pragma once
#include "screen.h"
#include "vec3.h"
#include "Line.h"
#include "Matrix.h"
#include <vector>

class Cube::protected PrimitiveObject { 
public:
	//constructor (requires, at the least, the screen variable)
	Cube(Screen& screen, vec3 position = {0.0f, 0.0f, 0.0f}, float size = 1); //forms the mesh of the cube, retrieves screenPtr, and gives the postion at which to spawn the cube in
private:
	//private attributes
	mesh cubeMesh; //the mesh of the cube is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as vec3s. vec3s are float(x, y, z)
};
