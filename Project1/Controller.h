#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>
#include <memory>

class Controller {
public:
	void ChangeControllerFocus(std::unique_ptr<WorldObjects>& worldObjectsPtr, std::unique_ptr<InputHandler>& inputHandlerPtr);
	PrimitiveObject* GetCurrentlyControlledObject();
	void InitializeIterator(std::unique_ptr<WorldObjects>& worldObjectsPtr);
private:
	std::unordered_map<std::string, PrimitiveObject*>::iterator selectedObject;
};
