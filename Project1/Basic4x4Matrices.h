#pragma once
#include <cmath>

class Matrix4x4 {
public:
	//operator overloaders
	Matrix4x4 operator=(const Matrix4x4& inputMatrix);
	Matrix4x4& operator*=(const Matrix4x4& other);
	//public attributes
	float matrix[4][4] = { 0 };
	//public methods
};

class RotationMatrix : public Matrix4x4 {
public:
	//constructor -- Initializes the general 4x4 rotation matrix. Multiply one matrix (particularly a 1x3, AKA vec3) by this matrix to perform the rotation. * operator is overloaded for this purpose
	RotationMatrix(float xRadians, float yRadians, float zRadians);
private:
	Matrix4x4 xRotationMatrix, yRotationMatrix, zRotationMatrix;
};