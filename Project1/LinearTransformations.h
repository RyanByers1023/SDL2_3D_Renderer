#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"

class LinearTransformations {
public:
	void ApplyTransformation(PrimitiveObject& object);
	void ApplyRotation(PrimitiveObject& object);
	//void ApplyScaling(PrimitiveObject& object, float scalar);
};
