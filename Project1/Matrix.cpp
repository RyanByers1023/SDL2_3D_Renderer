#include "Matrix.h"

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 Matrix4x4::operator=(const Matrix4x4& other) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] = other.matrix[i][j];
			}
		}
	}
	return result;
}

void Matrix4x4::MultiplyVec3Matrix4x4(const vec3& inputVector, vec3& outputVector) {

	outputVector.x = inputVector.x * this->matrix[0][0] + inputVector.y * this->matrix[1][0] + inputVector.z * this->matrix[2][0] + this->matrix[3][0];
	outputVector.y = inputVector.x * this->matrix[0][1] + inputVector.y * this->matrix[1][1] + inputVector.z * this->matrix[2][1] + this->matrix[3][1];
	outputVector.z = inputVector.x * this->matrix[0][2] + inputVector.y * this->matrix[1][2] + inputVector.z * this->matrix[2][2] + this->matrix[3][2];

	float w = inputVector.x * this->matrix[0][3] + inputVector.y * this->matrix[1][3] + inputVector.z * this->matrix[2][3] + this->matrix[3][3];

	if (w != 0.0f) {
		outputVector.x /= w;
		outputVector.y /= w;
		outputVector.z /= w;
	}
}