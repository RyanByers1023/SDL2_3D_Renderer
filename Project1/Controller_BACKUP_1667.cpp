#include "Controller.h"

<<<<<<< HEAD
void Controller::ChangeControllerFocus(const std::unique_ptr<WorldObjects>& worldObjectsPtr, const std::unique_ptr<InputHandler>& inputHandlerPtr) {
	if (selectedObject == worldObjectsPtr->objects.end()) { //this can occur when we spawn a new object in, always check for this when trying to access the selectedObject
		selectedObject = worldObjectsPtr->objects.begin();
	}

=======
void Controller::ChangeControllerFocus(std::shared_ptr<WorldObjects> worldObjectsPtr) {
>>>>>>> MajorRefactor
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
<<<<<<< HEAD
	return selectedObject->second; // Return the iterator in its current form for worldObject list
}

void Controller::InitializeIterator(const std::unique_ptr<WorldObjects>& worldObjectsPtr) {
	selectedObject = worldObjectsPtr->objects.begin();
=======
	return (selectedObject->second); // Return the iterator in its current form for worldObject list
>>>>>>> MajorRefactor
}