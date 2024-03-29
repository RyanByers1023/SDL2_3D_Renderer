#include "PrimitiveObject.h"

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
