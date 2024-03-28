#include "vec3.h"

vec3::vec3() {
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

vec3& vec3::operator*=(const Matrix4x4& transformationMatrix) {
    // Perform the transformation in place
    float newX = x * transformationMatrix.matrix[0][0] + y * transformationMatrix.matrix[1][0] + z * transformationMatrix.matrix[2][0] + transformationMatrix.matrix[3][0];
    float newY = x * transformationMatrix.matrix[0][1] + y * transformationMatrix.matrix[1][1] + z * transformationMatrix.matrix[2][1] + transformationMatrix.matrix[3][1];
    float newZ = x * transformationMatrix.matrix[0][2] + y * transformationMatrix.matrix[1][2] + z * transformationMatrix.matrix[2][2] + transformationMatrix.matrix[3][2];

    float w = x * transformationMatrix.matrix[0][3] + y * transformationMatrix.matrix[1][3] + z * transformationMatrix.matrix[2][3] + transformationMatrix.matrix[3][3];

    // If w is not zero, convert to Cartesian coordinates
    if (w != 0.0f) {
        newX /= w;
        newY /= w;
        newZ /= w;
    }

    // Update the components of the vector
    x = newX;
    y = newY;
    z = newZ;

    return *this;
}

vec3 vec3::operator*(const Matrix4x4& transformationMatrix) const {
    vec3 outputVector;

    outputVector.x = x * transformationMatrix.matrix[0][0] + y * transformationMatrix.matrix[1][0] + z * transformationMatrix.matrix[2][0] + transformationMatrix.matrix[3][0];
    outputVector.y = x * transformationMatrix.matrix[0][1] + y * transformationMatrix.matrix[1][1] + z * transformationMatrix.matrix[2][1] + transformationMatrix.matrix[3][1];
    outputVector.z = x * transformationMatrix.matrix[0][2] + y * transformationMatrix.matrix[1][2] + z * transformationMatrix.matrix[2][2] + transformationMatrix.matrix[3][2];

    float w = x * transformationMatrix.matrix[0][3] + y * transformationMatrix.matrix[1][3] + z * transformationMatrix.matrix[2][3] + transformationMatrix.matrix[3][3];

    if (w != 0.0f) {
        outputVector.x /= w;
        outputVector.y /= w;
        outputVector.z /= w;
    }

    return outputVector;
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