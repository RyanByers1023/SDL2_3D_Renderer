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
	void Draw(); //this passes all vertices and the pixels between them to the screen.vertices list.
	vec3 GetPosition(); //will return (x,y,z) coordinates. Undecided whether I should return north face bottom left or centeroid.
	void Rotate(); //rotates all of the vertices. Utilizes basic rotation matrix to accomplish. may change later to actually utilize the new 4x4matrix object thats been created for readability's sake
private:
	//private methods
	void CalcCenteroid(); //calculates the center point of the object. All vertices (x, y, z) are added using component wise addition, then they are all divided by the number of vertices using component wise division. This nets the centeroid
	//private attributes
	Screen* screenPtr; //this is the screen value that is used across many functions
	mesh cubeMesh; //the mesh of the cube is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as vec3s. vec3s are float(x, y, z)
	vec3 centeroid; //center coordinate of the cube. May return this as the position later on. Undecided if this would be a smart idea or not. Would be helpful in detecting collisions at least
	vec3 position; //this may be = to the centeroid. For now, this = the north face, bottom left vertice. The user provides this value when creating the cube.
	vec3 vertices[8]; //stores all of the vertices (corner points) of the cube, there are 8 vertices in a cube. Very helpful for calculating centeroid.
};
