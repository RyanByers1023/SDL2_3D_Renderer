#pragma once
#include "PrimitiveObject.h"

class Cube:public PrimitiveObject {
public:
	//constructor
	Cube(const Vec3& position = {0.0f, 0.0f, 40.0f}, const float& size = 1.0f, const string& name); //forms the mesh of the cube, retrieves screenPtr, and gives the postion at which to spawn the cube in
private:
	void InitalizeVertices();
};
