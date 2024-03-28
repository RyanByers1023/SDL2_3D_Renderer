#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"

class PrimitiveObject; // Forward declaration to avoid circular dependency issue with primitiveObject and LinearTransformations

class LinearTransformations {
public:
	//void ApplyTransformation(PrimitiveObject& object, vec3 dp);
	void ApplyRotation(PrimitiveObject& object);
	//void ApplyScaling(PrimitiveObject& object, float scalar);
};
