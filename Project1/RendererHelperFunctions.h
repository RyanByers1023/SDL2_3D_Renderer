#pragma once
#include "Vec2.h"
#include "Vec3.h"

bool ShouldRender(const Triangle3D tri, Vec3 normal, Vec3 cameraLocation);
Vec3 CalculateNormalVector(const Triangle3D tri);

