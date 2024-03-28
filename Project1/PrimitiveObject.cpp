#include "PrimitiveObject.h"

void PrimitiveObject::Draw() {
	for (auto& tri : primitiveMesh.triangles) {	
		triangle projectedTriangle;

		for (int i = 0; i < 3; i++) {
			projectedTriangle.p[i] = tri.p[i] * screenPtr->projMatrix;
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

	LinearTransformations transform;

	if (screenPtr->leftInput || screenPtr->rightInput || screenPtr->upInput || screenPtr->downInput) transform.ApplyRotation(*this); //FIX-ME--maybe best to include this in its own method later on...
	if (screenPtr->wInput || screenPtr->aInput || screenPtr->sInput || screenPtr->dInput) transform.ApplyTransformation(*this);
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

vec3 PrimitiveObject::GetCenteroid() {
	return this->centeroid; //return centroid of object
}
