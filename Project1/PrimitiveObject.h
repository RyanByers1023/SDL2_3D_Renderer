#pragma once
#include <vector>
#include "screen.h"
#include "Vec3.h"
#include "Line.h"

class PrimitiveObject {
public:
	//public attributes
	mesh primitiveMesh; //the mesh of the primitive 3-D object is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as Vec3s. Vec3s are float(x, y, z)
	std::vector<Vec3> vertices; //stores all of the vertices (corner points) of the object. Helpful in centeroid calculation. Mesh is formed from this vector
	Vec3 position; //Stores the north face, bottom left vertice. (first vertex in mesh)
	Vec3 centeroid; //center coordinate of the object.
	//public methods:
	void CalcCenteroid(); //adds all vertices together and divides by number of vertices. Centeroid stored as a Vec3
};

