#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"
#include "InputHandler.h"
#include "Time.h"

class LinearTransformations {
public:
	void ApplyTransformation(std::shared_ptr<InputHandler> inputHandlerPtr, std::shared_ptr<Time> timePtr, std::shared_ptr<PrimitiveObject> object);
	void ApplyRotation(std::shared_ptr<InputHandler> inputHandlerPtr, std::shared_ptr<Time> timePtr, std::shared_ptr<PrimitiveObject> object);
	//void ApplyScaling(std::shared_ptr<InputHandler> inputHandlerPtr, PrimitiveObject& object, std::shared_ptr<Time> timePtr, float scalar = 1.1f);
};
