#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"
#include "InputHandler.h"
#include "Time.h"
//#include <iostream>
#include <memory>

class LinearTransformations {
public:
	void ApplyTransformation(const std::unique_ptr<InputHandler>& inputHandlerPtr, const std::unique_ptr<Time>& timePtr, PrimitiveObject& object);
	void ApplyRotation(const std::unique_ptr<InputHandler> inputHandlerPtr, const std::unique_ptr<Time> timePtr, PrimitiveObject& object);
};
