#pragma once
#include <cmath>
#include <vector>

class vec3 { //a point (represented by floats) in 3-Space (x, y, z)
public:
	//contructors
	vec3();
	vec3(float x, float y, float z);
	vec3(int x, int y, int z);
	//public attributes
	float x;
	float y;
	float z;
	//public methods
	void Rotate(vec3 rotationVector);
};

struct triangle { //triangle = 3 x vec3 --> {(x, y, z), (x, y, z), (x, y, z)}
	vec3 p[3];
};

struct mesh {
	std::vector<triangle> triangles;
};
