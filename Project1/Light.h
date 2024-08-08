#pragma once
#include "Vec3.h"

class Light {
public:
	//3D coordinate position of light source
	Vec3 position;

	//RGB value; represents ambient (general, affects all objects within scene equally) color of light
	Vec3 ambient;

	//RGB value: represent diffuse (directional light), affected by angle between light direction & vertex normal
	Vec3 diffuse;

	//RGB value: represents specular (bright spots), affected by camera position & light direction
	Vec3 specular;

	//direction light is shining in, normalized (if isDirectional == true)
	Vec3 direction;

	//light can be directional, or emminate from a single point. if this value is not provided, it is assumed to be false
	bool isDirectional;

	//constructors:

	//directional light source
	Light(const Vec3& position, const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, const Vec3& direction, bool isDirectional)
		: position(position), ambient(ambient), diffuse(diffuse), specular(specular), direction(direction), isDirectional(isDirectional) {}

	//point light source
	Light(const Vec3& position, const Vec3& ambient, const Vec3& diffuse, const Vec3& specular, const Vec3& direction)
		: position(position), ambient(ambient), diffuse(diffuse), specular(specular), direction(direction), isDirectional(false) {}

	//clamps all RGB values between 0.0 and 1.0
	void ClampColors();
private:
	Vec3 Clamp(const Vec3& color);
};