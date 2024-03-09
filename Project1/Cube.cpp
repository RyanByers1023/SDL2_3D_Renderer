#include "Cube.h"

Cube::Cube(Screen& screen, vec3 position, float size){ //default dimensions: 1px x 1px x 1px
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
	cubeMesh.triangles = {
		// SOUTH FACE
		{vertices[0], vertices[3], vertices[2]},
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

void Cube::Draw() {
	for (auto& triangle : cubeMesh.triangles) {
		float x1 = triangle.p[0].x;
		float y1 = triangle.p[0].y;

		float x2 = triangle.p[1].x;
		float y2 = triangle.p[1].y;

		float x3 = triangle.p[2].x;
		float y3 = triangle.p[2].y;

		Line line1(*screenPtr, x1, y1, x2, y2); //first line of triangle (side a)
		line1.Draw();

		Line line2(*screenPtr, x2, y2, x3, y3); //second line of triangle (side b)
		line2.Draw();

		Line line3(*screenPtr, x3, y3, x1, y1); //third line of trianle (side c) -- this is the hypotenuse
		line3.Draw();
	}

	if (screenPtr->leftInput || screenPtr->rightInput || screenPtr->upInput || screenPtr->downInput) Rotate();
}

void Cube::CalcCenteroid() {
	// Initialize sums for x, y, and z coordinates
	float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;

	// Iterate through all vertices and sum up coordinates
	for (const auto& vertex : vertices) {
		sumX += vertex.x;
		sumY += vertex.y;
		sumZ += vertex.z;
	}

	// Calculate average coordinates (centroid)
	float avgX = sumX / 8.0f;
	float avgY = sumY / 8.0f;
	float avgZ = sumZ / 8.0f;

	centeroid = { avgX, avgY, avgZ };
}

void Cube::Rotate() {
	for (auto& triangle : cubeMesh.triangles) {
		for (int i = 0; i < 3; i++) {
			triangle.p[i].x -= centeroid.x;
			triangle.p[i].y -= centeroid.y;
			triangle.p[i].z -= centeroid.z;
		}
		for (int i = 0; i < 3; i++) {
			if (screenPtr->leftInput) {	
				triangle.p[i].rotate(0.000, -0.010, 0); //rotate right
			}
			if (screenPtr->rightInput) {
				triangle.p[i].rotate(0.000, 0.010, 0); //rotate left
			}
			if (screenPtr->upInput) {
				triangle.p[i].rotate(0.010, 0.000, 0); //rotate upwards
			}
			if (screenPtr->downInput) {
				triangle.p[i].rotate(-0.010, 0.000, 0); //rotate downwards
			}	
		}
		for (int i = 0; i < 3; i++) {
			triangle.p[i].x += centeroid.x;
			triangle.p[i].y += centeroid.y;
			triangle.p[i].z += centeroid.z;
		}
	}
}

vec3 Cube::GetPosition() {
	return centeroid;
}