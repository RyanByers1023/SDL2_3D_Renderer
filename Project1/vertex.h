#pragma once
#include <cmath>
#include <vector>

struct vec3 {
	float x, y, z;
};

struct mat4x4 {
	float m[4][4] = { 0 };
};

//might get rid of this
class vertex {
public:
	//contructors
	vertex(float x, float y, float z);
	vertex(vec3 point);
	//public attributes
	float x;
	float y;
	float z;
	//public methods
	void rotate(float x, float y, float z);
private:
	//private attributes
	vec3 point;
};

struct triangle {
	vertex p[3];
};

struct mesh {
	std::vector<triangle> triangles;
};
