#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"
#include "InputHandler.h"
#include "Time.h"

class LinearTransformations {
public:
	void ApplyTransformation(InputHandler* inputHandlerPtr, Time* timePtr, PrimitiveObject& object);
	void ApplyRotation(InputHandler* inputHandlerPtr, Time* timePtr, PrimitiveObject& object);
	void ApplyScaling(InputHandler* inputHandlerPtr, PrimitiveObject& object, Time* timePtr, float scalar = 1.1f);
};
