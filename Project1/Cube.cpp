#include "Cube.h"

Cube::Cube(Screen& screen, vec3 position, float size) : Cube(){ //default dimensions: 1px x 1px x 1px
	this->screenPtr = &screen;
	this->position = position;

	// Definition of the vertices of the cube
	vertices[0] = { position.x, position.y, position.z };                        // (0, 0, 0)
	vertices[1] = { position.x + size, position.y, position.z };                 // (1, 0, 0)
	vertices[2] = { position.x + size, position.y + size, position.z };          // (1, 1, 0)
	vertices[3] = { position.x, position.y + size, position.z };                 // (0, 1, 0)
	vertices[4] = { position.x, position.y, position.z + size };                 // (0, 0, 1)
	vertices[5] = { position.x + size, position.y, position.z + size };          // (1, 0, 1)
	vertices[6] = { position.x + size, position.y + size, position.z + size };   // (1, 1, 1)
	vertices[7] = { position.x, position.y + size, position.z + size }; ;		 // (0, 1, 1)

	//use the above vertices of the cube to make the cube mesh
	//built in a counterclockwise fashion
	cubeMesh.triangles = {
		// SOUTH FACE
		{vertices[0], vertices[3], vertices[2]}, //{vec3, vec3, vec3} ---> {(x, y, z), (x, y, z), (x, y, z)}
		{vertices[0], vertices[2], vertices[1]},

		// EAST FACE
		{vertices[1], vertices[2], vertices[6]},
		{vertices[1], vertices[6], vertices[5]},

		// NORTH FACE
		{vertices[5], vertices[6], vertices[7]},
		{vertices[5], vertices[7], vertices[4]},

		// WEST FACE
		{vertices[4], vertices[7], vertices[3]},
		{vertices[4], vertices[3], vertices[0]},

		// TOP FACE
		{vertices[3], vertices[7], vertices[6]},
		{vertices[3], vertices[6], vertices[2]},

		// BOTTOM FACE
		{vertices[4], vertices[0], vertices[1]},
		{vertices[4], vertices[1], vertices[5]}
	};

	CalcCenteroid();
}