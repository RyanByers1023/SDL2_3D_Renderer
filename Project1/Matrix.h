#pragma once
#include "vec3.h"

class Matrix4x4 {
public:
	//operator overloaders
	Matrix4x4 operator*(const Matrix4x4& other);
	Matrix4x4 operator=(const Matrix4x4& other);
	//public attributes
	float matrix[4][4] = { 0 };
	//public methods
	void MultiplyVec3Matrix4x4(const vec3& inputVector, vec3& outputVector);
};