#pragma once
#include <cmath>
#include <vector>

class vec3 {
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
	void rotate(vec3 rotationVector);
};

struct triangle {
	vec3 p[3];
};

struct mesh {
	std::vector<triangle> triangles;
};
