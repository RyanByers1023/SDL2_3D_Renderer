#include "vec3.h"
#include <vector>

vec3::vec3() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3::vec3(int x, int y, int z) {
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
	this->z = static_cast<float>(z);
}

void vec3::Rotate(vec3 rotationVector) { //values x, y, and z must = desired rotations in radians.
	float rad = 0;

	rad = rotationVector.x;
	this->y = cos(rad) * this->y - sin(rad) * this->z;
	this->z = sin(rad) * this->y + cos(rad) * this->z;

	rad = rotationVector.y;
	this->x = cos(rad) * this->x + sin(rad) * this->z;
	this->z = -sin(rad) * this->x + cos(rad) * this->z;

	rad = rotationVector.z;
	this->x = cos(rad) * this->x - sin(rad) * this->y;
	this->y = sin(rad) * this->x + cos(rad) * this->y;
}