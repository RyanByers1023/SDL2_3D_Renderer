#pragma once
#include "Vec3.h"
class Material {
public:
	//RGB value: base color under ambient light
	Vec3 ambient;

	//RGB value: base color under diffuse light
	Vec3 diffuse;

	//RGB value: color of specular highlights
	Vec3 specular;

	//controls size and intensity of specular highlights
	float shininess;

	//constructor:
	Material(const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, const float& shininess)
		: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
};
