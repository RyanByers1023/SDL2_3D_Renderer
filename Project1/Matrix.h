#pragma once

class Matrix {
public:
	//operator overloaders
	Matrix operator*(const Matrix& other);
	Matrix operator=(const Matrix& other);
	//public attributes
	float matrix[4][4] = { 0 };
};