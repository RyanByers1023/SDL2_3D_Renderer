#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"
#include "InputHandler.h"
#include "Time.h"
#include <memory>

class LinearTransformations {
public:
	void ApplyTransformation(std::unique_ptr<InputHandler>& inputHandlerPtr, std::unique_ptr<Time>& timePtr, PrimitiveObject& object);
	void ApplyRotation(std::unique_ptr<InputHandler>& inputHandlerPtr, std::unique_ptr<Time>& timePtr, PrimitiveObject& object);
};
