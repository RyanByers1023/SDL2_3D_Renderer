#include "Controller.h"

void Controller::ChangeControllerFocus(std::shared_ptr<WorldObjects> worldObjectsPtr) {
	if (inputHandlerPtr->qInput) {
		SDL_Delay(50); //delay to prevent multiple inputs from being registered
		if (selectedObject == worldObjectsPtr->objects.begin()) {
			selectedObject = worldObjectsPtr->objects.end(); //if we reach the beginning of the unordered_map, loop back to the end
		}
		selectedObject--; //move to the previous object in the worldObjects unordered_map
	}

	 if (inputHandlerPtr->eInput) {
		SDL_Delay(50); //delay to prevent multiple inputs from being registered
		selectedObject++; //move to the next object in the worldObjects unordered_map
		if (selectedObject == worldObjectsPtr->objects.end()) {
			selectedObject = worldObjectsPtr->objects.begin(); //if we reach the end of the unordered_map, loop back to the beginning
		}
	 }

	 // Ensure selectedObject is valid before using
	 if (selectedObject == worldObjectsPtr->objects.end()) {
		 std::cerr << "selectedObject is out of bounds" << std::endl;
		 return;
	 }
}

std::shared_ptr<PrimitiveObject> Controller::GetCurrentlyControlledObject() {
	return (selectedObject->second); // Return the iterator in its current form for worldObject list
}