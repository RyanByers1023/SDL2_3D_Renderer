#include "Vec2.h"


//assignment operator to assign from Vec3
Vec2& Vec2::operator=(const Vec3& otherVector) {
	x = otherVector.x;
	y = otherVector.y;
	return *this;
}
