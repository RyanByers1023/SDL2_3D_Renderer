#pragma once
#include <vector>
#include "screen.h"
#include "vec3.h"
#include "Line.h"

class PrimitiveObject {
	//public methods
public:
	//public getters
	vec3 GetCenteroid(); //will return the center point of the object
	//public attributes
	mesh primitiveMesh; //the mesh of the primitive 3-D object is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as vec3s. vec3s are float(x, y, z)
	Screen* screenPtr; //access to screen via a pointer value. (SDL2 requires this variable for many operations)
	std::vector<vec3> vertices; //stores all of the vertices (corner points) of the object. Helpful in centeroid calculation.
	vec3 position; //Stores the north face, bottom left vertice. (first vertex in mesh)	
	//public methods:
	void CalcCenteroid(); //adds all vertices together and divides by number of vertices. Centeroid stored as a vec3
protected:
	//protected attributes
	vec3 centeroid; //center coordinate of the object.
};

