#pragma once
#include <vector>
#include "Basic4x4Matrices.h"

//point (represented by floats) in 3-D (x, y, z)
class Vec3{ 
 
public:
	//default constructor
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {};

	//constructor with float parameters
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {};

	//contructor with int parameters
	Vec3(int x, int y, int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {};

	//*= operator overloader
	Vec3& operator*=(const Matrix4x4& transformationMatrix);

	//* operator overloader
	Vec3 operator*(const Matrix4x4& transformationMatrix) const;

	//public member variables
	float x;
	float y;
	float z;
};

//triangle = 3 x Vec3 --> {(x, y, z), (x, y, z), (x, y, z)}
struct Triangle3D { 
	Vec3 point[3];
};

struct mesh {
	std::vector<Triangle3D> triangles;
};
