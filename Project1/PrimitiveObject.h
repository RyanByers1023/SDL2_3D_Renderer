#pragma once
#include <vector>
#include <string>
#include "screen.h"
#include "Vec3.h"
#include "Line.h"

class PrimitiveObject {
public:
	//constructor
	PrimitiveObject(Vec3 position, float size) 
		: position(position), size(size) {}

	virtual void InitializeMesh() = 0;

	//public attributes:

	//the mesh of the primitive 3-D object is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as Vec3s. Vec3s are float(x, y, z)
	mesh primitiveMesh; 

	//stores all of the vertices of the object. Mesh is formed from this vector
	std::vector<Vec3> vertices;

	//Stores the north face, bottom left vertice. (this is considered the first vertex in mesh)
	Vec3 position; 

	//a scalar that determines how large the object is
	float size; 

	//center coordinate of the object in 3-space
	Vec3 centeroid;

	//public methods:

	//adds all vertices together and divides by number of vertices. Centeroid stored as a Vec3
	void CalcCenteroid(); 
};

