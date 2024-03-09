#include "vertex.h"
#include <vector>

vertex::vertex(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	vec3 newPoint = { x, y, z };
	this->point = newPoint;
}

vertex::vertex(vec3 point) {
	this->x = point.x;
	this->y = point.y;
	this->z = point.z;
	this->point = point;
}

void vertex::rotate(float x, float y, float z) { //values x, y, and z must = desired rotations in radians.
	float rad = 0;

	rad = x;
	this->y = cos(rad) * this->y - sin(rad) * this->z;
	this->z = sin(rad) * this->y + cos(rad) * this->z;

	rad = y;
	this->x = cos(rad) * this->x + sin(rad) * this->z;
	this->z = -sin(rad) * this->x + cos(rad) * this->z;

	rad = z;
	this->x = cos(rad) * this->x - sin(rad) * this->y;
	this->y = sin(rad) * this->x + cos(rad) * this->y;
}