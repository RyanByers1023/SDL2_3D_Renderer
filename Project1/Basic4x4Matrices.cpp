#include "Basic4x4Matrices.h"

Matrix4x4 Matrix4x4::operator=(const Matrix4x4& inputMatrix) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] = inputMatrix.matrix[i][j];
			}
		}
	}
	return result;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.matrix[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
			}
		}
	}
	*this = result; // Update the current matrix with the result
	return *this;
}

//Linear Transformation Matrices:

RotationMatrix::RotationMatrix(float xRadians, float yRadians, float zRadians) {

	//Alpha == z-axis rotation, Beta == y-axis rotation, Gamma = x-axis rotation

	float cosAlpha = cos(zRadians);
	float cosBeta = cos(yRadians);
	float cosGamma = cos(xRadians);
	float sinAlpha = sin(zRadians);
	float sinBeta = sin(yRadians);
	float sinGamma = sin(xRadians);

	//formation of the general 3-D rotation matrix
	this->xRotationMatrix.matrix[0][0] = cosBeta * cosAlpha;
	this->xRotationMatrix.matrix[0][1] = cosBeta * sinAlpha;
	this->xRotationMatrix.matrix[0][2] = -sinBeta;
	this->xRotationMatrix.matrix[1][0] = sinGamma * sinBeta * cosAlpha - cosGamma * sinAlpha;
	this->xRotationMatrix.matrix[1][1] = sinGamma * sinBeta * sinAlpha + cosGamma * cosAlpha;
	this->xRotationMatrix.matrix[1][2] = sinGamma * cosBeta;
	this->xRotationMatrix.matrix[2][0] = cosGamma * sinBeta * cosAlpha + sinGamma * sinAlpha;
	this->xRotationMatrix.matrix[2][1] = cosGamma * sinBeta * sinAlpha - sinGamma * cosAlpha;
	this->xRotationMatrix.matrix[2][2] = cosGamma * cosBeta;

	// Set the last row and column to maintain a 3x3 rotation matrix
	this->xRotationMatrix.matrix[3][0] = 0;
	this->xRotationMatrix.matrix[3][1] = 0;
	this->xRotationMatrix.matrix[3][2] = 0;
	this->xRotationMatrix.matrix[0][3] = 0;
	this->xRotationMatrix.matrix[1][3] = 0;
	this->xRotationMatrix.matrix[2][3] = 0;
	this->xRotationMatrix.matrix[3][3] = 1;
}