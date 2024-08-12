#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

class Controller {
public:
	Controller(std::shared_ptr<InputHandler> inputHandlerPtr) : inputHandlerPtr(inputHandlerPtr) {}
	std::shared_ptr<PrimitiveObject> GetCurrentlyControlledObject();
	void ChangeControllerFocus(std::shared_ptr<WorldObjects> worldObjectsPtr);
private:
	void RevalidateSelectedObject(std::shared_ptr<WorldObjects> worldObjectsPtr);
	std::shared_ptr<InputHandler> inputHandlerPtr;
	std::unordered_map<std::string, std::shared_ptr<PrimitiveObject>>::iterator selectedObject;
};
