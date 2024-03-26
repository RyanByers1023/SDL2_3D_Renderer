#include "Matrix.h"

Matrix Matrix::operator*(const Matrix& other) {
	Matrix result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::operator=(const Matrix& other) {
	Matrix result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.matrix[i][j] = other.matrix[i][j];
			}
		}
	}
	return result;
}