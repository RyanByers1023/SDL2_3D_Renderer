#include "Cube.h"

Cube::Cube(std::string name, Vec3 position, float size){ //Default dimensions: 1px x 1px x 1px. Default position = {0, 0, 0} - origin. Below commented values are constructed with these inputs in mind as an example
	this->position = position;
	this->name = name;

	// Definition of the vertices of the cube
	vertices.push_back({ position.x, position.y, position.z });                        // (0, 0, 0) --- [0]
	vertices.push_back({ position.x + size, position.y, position.z });                 // (1, 0, 0) --- [1]
	vertices.push_back({ position.x + size, position.y + size, position.z });          // (1, 1, 0) --- [2]
	vertices.push_back({ position.x, position.y + size, position.z });                 // (0, 1, 0) --- [3] ----> 8 total vertices
	vertices.push_back({ position.x, position.y, position.z + size });                 // (0, 0, 1) --- [4]
	vertices.push_back({ position.x + size, position.y, position.z + size });          // (1, 0, 1) --- [5]
	vertices.push_back({ position.x + size, position.y + size, position.z + size });   // (1, 1, 1) --- [6]
	vertices.push_back({ position.x, position.y + size, position.z + size }); ;		   // (0, 1, 1) --- [7]

	//use the above vertices of the cube to make the cube mesh
	primitiveMesh.triangles = {
		// SOUTH FACE
		{vertices[0], vertices[3], vertices[2]}, //{Vec3, Vec3, Vec3} ---> {(x, y, z), (x, y, z), (x, y, z)}
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