#pragma once
#include "Basic4x4Matrices.h"
#include "PrimitiveObject.h"
#include "InputHandler.h"
#include "Time.h"
#include <memory>

class LinearTransformations {
public:
	void ApplyTransformation(const std::unique_ptr<InputHandler>& inputHandlerPtr, const std::unique_ptr<Time>& timePtr, std::unique_ptr<PrimitiveObject>& object) const;
	void ApplyRotation(const std::unique_ptr<InputHandler>& inputHandlerPtr, const std::unique_ptr<Time>& timePtr, std::unique_ptr<PrimitiveObject>& object) const;
};
