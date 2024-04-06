#include "Vec2.h"

Vec2::Vec2() {
	this->x = 0.0f;
	this->y = 0.0f;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2::Vec2(int x, int y) {
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
}

Vec2& Vec2::operator=(const Vec3& otherVector) {
	x = otherVector.x;
	y = otherVector.y;
	return *this;
}