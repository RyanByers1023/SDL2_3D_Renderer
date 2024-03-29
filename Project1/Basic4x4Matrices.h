#pragma once
#include <cmath>
#include "screen.h"

class Matrix4x4 {
public:
	//operator overloaders
	Matrix4x4 operator=(const Matrix4x4& inputMatrix);
	Matrix4x4& operator*=(const Matrix4x4& other);
	//public attributes
	float matrix[4][4] = { 0 };
	//public methods
};

class ProjectionMatrix : public Matrix4x4 {
public:
	//constructor -- Initializes the projection matrix
	ProjectionMatrix(Screen& screen, float fov = 90.0f, float fFar = 1000.0f, float fNear = 0.1f);
};

class RotationMatrix : public Matrix4x4 {
public:
	//constructor -- Initializes the general 4x4 rotation matrix. Multiply one matrix (particularly a 1x3, AKA vec3) by this matrix to perform the rotation. * operator is overloaded for this purpose
	RotationMatrix(float xRadians, float yRadians, float zRadians);
};