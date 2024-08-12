#pragma once
#include "InputHandler.h"
#include "PrimitiveObject.h"
#include "WorldObjects.h"
#include <string>
#include <unordered_map>
#include <memory>

class Controller {
public:
	Controller(WorldObjects* worldObjectsPtr) : worldObjectsPtr(worldObjectsPtr), selectedObject(worldObjectsPtr->objects.begin()) {};
	void ChangeControllerFocus(std::unique_ptr<InputHandler>& inputHandlerPtr);
	PrimitiveObject* GetCurrentlyControlledObject();
private:
	WorldObjects* worldObjectsPtr;
	std::unordered_map<std::string, PrimitiveObject>::iterator selectedObject;
};
