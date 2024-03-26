#pragma once

class Matrix {
public:
	//default contructor
	Matrix();
	//operator overloaders
	Matrix operator*(const Matrix& other);
	Matrix operator=(const Matrix& other);
	//public attributes
	float matrix[4][4] = { 0 };
};