#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>

class Controller {
public:
	Controller(InputHandler* inputHandlerPtr, WorldObjects* worldObjectsPtr) : inputHandlerPtr(inputHandlerPtr), worldObjectsPtr(worldObjectsPtr), selectedObject(worldObjectsPtr->objects.begin()) {};
	PrimitiveObject* GetCurrentlyControlledObject();
	void ChangeControllerFocus();
private:
	InputHandler* inputHandlerPtr;
	WorldObjects* worldObjectsPtr;
	std::unordered_map<std::string, PrimitiveObject>::iterator selectedObject;
};
