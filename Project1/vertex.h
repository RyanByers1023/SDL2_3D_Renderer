#pragma once
#include <cmath>
#include <vector>

struct vec3 {
	float x, y, z;
};

struct mat4x4 {
	float m[4][4] = { 0 };
};

mat4x4 multiplyMatrices(const mat4x4& mat1, const mat4x4& mat2) {
	mat4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
			}
		}
	}

	return result;
}


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
