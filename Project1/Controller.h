#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>
#include <memory>

class Controller {
public:

	//return the next object in worldObjectsPtr
	void ChangeControllerFocus(const std::unique_ptr<InputHandler>& inputHandlerPtr, const std::unique_ptr<WorldObjects>& worldObjectsPtr);
private:
	//iterator dictates which object user input will have effect on. Iterates through worldObjects
	std::unordered_map<std::string, std::shared_ptr<PrimitiveObject>>::iterator selectedObject; 
};
