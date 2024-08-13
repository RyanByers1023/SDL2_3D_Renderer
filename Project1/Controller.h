#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>
#include <memory>

class Controller {
public:
	void ChangeControllerFocus(const std::unique_ptr<WorldObjects>& worldObjectsPtr, const std::unique_ptr<InputHandler>& inputHandlerPtr);
	std::shared_ptr<PrimitiveObject> GetCurrentlyControlledObject();
	void InitializeIterator(const std::unique_ptr<WorldObjects>& worldObjectsPtr);
private:
	std::unordered_map<std::string, std::shared_ptr<PrimitiveObject>>::iterator selectedObject;
};
