#pragma once
#include "PrimitiveObject.h"

class Cube:public PrimitiveObject {
public:
	//constructor (requires, at the least, the screen variable)
	Cube(Screen& screen, vec3 position = {0.0f, 0.0f, 0.0f}, float size = 1); //forms the mesh of the cube, retrieves screenPtr, and gives the postion at which to spawn the cube in
	Cube() : vertices(8) {}; //initilization constructor that initializes the vertices vector with a size of 8. runs when the above constructor runs
private:
	//private attributes
	mesh cubeMesh; //the mesh of the cube is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as vec3s. vec3s are float(x, y, z)
	std::vector<vec3> vertices; //initialized with a size of 8
};
