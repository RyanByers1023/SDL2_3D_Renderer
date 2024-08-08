#include "Vec3.h"

//handle addition of vectors
Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

//handle in place addition
Vec3& Vec3::operator+=(const Vec3& other){
    x + other.x;
    y + other.y;
    z + other.z;
    return *this;
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3& Vec3::operator-(const Vec3& other) {
    x - other.x;
    y - other.y;
    z - other.z;
    return *this;
}

Vec3 Vec3::operator*(const Vec3& other) const {
    return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3& Vec3::operator*(const Vec3& other) {
    x* other.x;
    y* other.y;
    z* other.z;
    return *this;
}

//handle vec3 scalar division
Vec3 Vec3::operator/(const float& scalar) const {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

bool Vec3::operator<(const Vec3& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return z < other.z;
}

//used for rotations, transforms, etc.
Vec3& Vec3::operator*=(const Matrix4x4& transformationMatrix) {
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

//used for rotations, transforms, etc.
Vec3& Vec3::operator*(const Matrix4x4& transformationMatrix) const {
    Vec3 outputVector;

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


//used for projecting 3d -> 2d
Vec2 Vec3::operator*(const ProjectionMatrix* projectionMatrix) const {

    float newX = x * projectionMatrix->matrix[0][0] + y * projectionMatrix->matrix[1][0] + z * projectionMatrix->matrix[2][0] + projectionMatrix->matrix[3][0];
    float newY = x * projectionMatrix->matrix[0][1] + y * projectionMatrix->matrix[1][1] + z * projectionMatrix->matrix[2][1] + projectionMatrix->matrix[3][1];
    float newZ = x * projectionMatrix->matrix[0][2] + y * projectionMatrix->matrix[1][2] + z * projectionMatrix->matrix[2][2] + projectionMatrix->matrix[3][2];

    float w = x * projectionMatrix->matrix[0][3] + y * projectionMatrix->matrix[1][3] + z * projectionMatrix->matrix[2][3] + projectionMatrix->matrix[3][3];

    // If w is not zero, convert to Cartesian coordinates
    if (w != 0.0f) {
        newX /= w;
        newY /= w;
        newZ /= w;
    }

    // Return the 2D vector
    return Vec2(newX, newY);
}

//return a normal unit vector
Vec3 Vec3::Normalize() const {
    float length = (x * x + y * y + z * z);

    return Vec3(x / length, y / length, z / length);
}