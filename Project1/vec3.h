#pragma once
#include <vector>
#include <map>
#include "Basic4x4Matrices.h"

//point (represented by floats) in 3-D (x, y, z)
class Vec3{ 
 
public:
	//default constructor
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {}; //initialize to zero vector

	//constructor with float parameters
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {};

	//contructor with int parameters
	Vec3(int x, int y, int z) : x(static_cast<float>(x)), y(static_cast<float>(y)), z(static_cast<float>(z)) {};

	//handle addition of vectors
	Vec3 operator+(const Vec3& other) const;

	//handle addition of vectors (by reference)
	Vec3& operator+=(const Vec3& other);

	//handle subtraction of vectors
	Vec3 operator-(const Vec3& other) const;

	//handle subtraction of vectors (by reference)
	Vec3& operator-(const Vec3& other);

	//handle multiplication of vectors
	Vec3 operator*(const Vec3& other) const;

	//handle multiplication of vectors (by reference)
	Vec3& operator*(const Vec3& other);

	//handle vec3 scalar division
	Vec3 operator/(const float& scalar) const;

	//handle <operator (for the purpose of storing Vec3s in map of std::map<Vec3, Vec3>)
	bool operator<(const Vec3& other) const;

	//*= operator overloader for Matrix4x4
	Vec3& operator*=(const Matrix4x4& transformationMatrix);

	//Vec3& * Matrix4x4 operator overloader
	Vec3& operator*(const Matrix4x4& transformationMatrix) const;

	Vec2 operator*(const ProjectionMatrix* projectionMatrix) const;

	//normalize this vector
	Vec3 Normalize() const;

	//public member variables
	float x;
	float y;
	float z;
};

//triangle = 3 x Vec3 --> {(x, y, z), (x, y, z), (x, y, z)}
class Triangle3D { 
public:
	//default constuctor
	Triangle3D() : faceNormal(0.0f, 0.0f, 0.0f) {}
	//constructor for intializer lists
	Triangle3D(const Vec3& v1, const Vec3& v2, const Vec3& v3) : vertices{ v1, v2, v3 }, faceNormal(0.0f, 0.0f, 0.0f) {}

	Vec3 vertices[3];
	Vec3 vertexNormals[3];
	Vec3 faceNormal;
};

//stores entire mesh (comprised of triangles)
struct mesh {
	std::vector<Triangle3D> triangles; //the mesh
	std::map<Vec3, Vec3> vertexNormalMap; //normals corresponding to each vertex
};
