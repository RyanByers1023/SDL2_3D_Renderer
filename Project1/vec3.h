#pragma once
#include <vector>
#include "Basic4x4Matrices.h"

class Vec3{ //a point (represented by floats) in 3-Space (x, y, z)
 
public:
	//contructors
	Vec3();
	Vec3(float x, float y, float z);
	Vec3(int x, int y, int z);
	//overloaders
	Vec3& operator*=(const Matrix4x4& transformationMatrix);
	Vec3 operator*(const Matrix4x4& transformationMatrix) const;
	//public attributes
	float x;
	float y;
	float z;
};

struct Triangle3D { //triangle = 3 x Vec3 --> {(x, y, z), (x, y, z), (x, y, z)}
	Vec3 point[3];
};

struct mesh {
	std::vector<Triangle3D> triangles;
};
