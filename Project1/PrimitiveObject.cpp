#include "PrimitiveObject.h"

void PrimitiveObject::Draw() {
	for (auto& tri : primitiveMesh.triangles) {	
		triangle projectedTriangle;

		for (int i = 0; i < 3; i++) {
			screenPtr->projMatrix.MultiplyVec3Matrix4x4(tri.p[i], projectedTriangle.p[i]);
		}

		projectedTriangle.p[0].x += 1.0f; projectedTriangle.p[0].y += 1.0f;
		projectedTriangle.p[1].x += 1.0f; projectedTriangle.p[1].y += 1.0f;
		projectedTriangle.p[2].x += 1.0f; projectedTriangle.p[2].y += 1.0f;

		float halfScreenWidth = static_cast<float>(screenPtr->width) * 0.5f;
		float halfScreenHeight = static_cast<float>(screenPtr->height) * 0.5f;

		projectedTriangle.p[0].x *= halfScreenWidth;
		projectedTriangle.p[0].y *= halfScreenHeight;
		projectedTriangle.p[1].x *= halfScreenWidth;
		projectedTriangle.p[1].y *= halfScreenHeight;
		projectedTriangle.p[2].x *= halfScreenWidth;
		projectedTriangle.p[2].y *= halfScreenHeight;

		float x1 = projectedTriangle.p[0].x;
		float y1 = projectedTriangle.p[0].y;

		float x2 = projectedTriangle.p[1].x;
		float y2 = projectedTriangle.p[1].y;

		float x3 = projectedTriangle.p[2].x;
		float y3 = projectedTriangle.p[2].y;

		Line line1(*screenPtr, x1, y1, x2, y2); //first line of triangle (side a)
		line1.Draw();

		Line line2(*screenPtr, x2, y2, x3, y3); //second line of triangle (side b)
		line2.Draw();

		Line line3(*screenPtr, x3, y3, x1, y1); //third line of triangle (side c) -- this is the hypotenuse
		line3.Draw();
	}

	if (screenPtr->leftInput || screenPtr->rightInput || screenPtr->upInput || screenPtr->downInput) Rotate(); //FIX-ME--maybe best to include this in its own method later on...
}

void PrimitiveObject::CalcCenteroid() {
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

	this->centeroid = { avgX, avgY, avgZ };
}

void PrimitiveObject::Rotate() {
	float negativeRotation = -1.0; //modifies how fast rotation occurs
	float positiveRotation = 1.0; 
	negativeRotation *= screenPtr->deltaTime; //normalize rotation
	positiveRotation *= screenPtr->deltaTime; 

	for (auto& triangle : this->primitiveMesh.triangles) {
		for (int i = 0; i < 3; i++) {
			triangle.p[i].x -= centeroid.x;
			triangle.p[i].y -= centeroid.y;
			triangle.p[i].z -= centeroid.z;
		}
		for (int i = 0; i < 3; i++) {
			if (screenPtr->leftInput) {	
				vec3 leftRotation = { 0.00f, negativeRotation, 0.00f };;
				triangle.p[i].Rotate(leftRotation); //Rotate left
			}
			if (screenPtr->rightInput) {
				vec3 rightRotation = { 0.00f, positiveRotation, 0.00f };
				triangle.p[i].Rotate(rightRotation); //Rotate right
			}
			if (screenPtr->upInput) {
				vec3 upRotation = { positiveRotation, 0.00f, 0.00f };
				triangle.p[i].Rotate(upRotation); //Rotate upwards
			}
			if (screenPtr->downInput) {
				vec3 downRotation = { negativeRotation, 0.00f, 0.00f };
				triangle.p[i].Rotate(downRotation); //Rotate downwards
			}	
		}
		for (int i = 0; i < 3; i++) {
			triangle.p[i].x += this->centeroid.x;
			triangle.p[i].y += this->centeroid.y;
			triangle.p[i].z += this->centeroid.z;
		}
	}
}

vec3 PrimitiveObject::GetPosition() {
	return this->vertices[0]; //return corner point of object
}

vec3 PrimitiveObject::GetCenteroid() {
	return this->centeroid; //return centroid of object
}
