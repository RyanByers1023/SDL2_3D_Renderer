#pragma once
#include "PrimitiveObject.h"

class Cube:public PrimitiveObject {
public:
	//constructor
	Cube(Screen& screen, vec3 position = {0.0f, 0.0f, 0.0f}, float size = 1); //forms the mesh of the cube, retrieves screenPtr, and gives the postion at which to spawn the cube in
};
