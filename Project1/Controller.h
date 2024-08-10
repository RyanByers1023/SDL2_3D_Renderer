#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>
#include <memory>

class Controller {
public:
	//getter: returns selectedObject->object (*PrimitiveObject)
	std::shared_ptr<PrimitiveObject> GetCurrentlyControlledObject();

	//perform 1 iteration of selectedObject through worldObjects
	void ChangeControllerFocus(std::shared_ptr<InputHandler> inputHandlerPtr, std:;shared_ptr<WorldObjects> worldObjectsPtr);
private:
	//iterator dictates which object user input will have effect on. Iterates through worldObjects
	std::unordered_map<std::string, PrimitiveObject>::iterator selectedObject; 
};
