#include "StartMe.h"

StartMe::StartMe(const int windowWidth, const int windowHeight) {
	inputHandlerPtr = std::make_unique<InputHandler>();
	timePtr = std::make_unique<Time>();
	worldObjectsPtr = std::make_unique<WorldObjects>();
	controllerPtr = std::make_unique<Controller>();
	rendererPtr = std::make_unique<Renderer>(windowWidth, windowHeight);
}

void StartMe::StartRendering() {
	//spawner contains methods relevant to creating new game objects in the world space
	Spawner spawner;

	//spawner needs a unique name for the object to be spawned, hardcoded as "cube1" for now.
	spawner.SpawnCube(worldObjectsPtr, "cube1"); 

	//get the currently selected object
	std::unique_ptr<PrimitiveObject> selectedObject = controllerPtr->GetCurrentlyControlledObject(); 

	//intialize controller, select first object in map to control
	controllerPtr->InitializeIterator(worldObjectsPtr); 

	//enter main rendering loop:
	while (true) {
		//calculate the time since the last frame has occured, store this value as attribute deltaTime
		timePtr->Tick();

		//render everything in worldObjects (that is within the player's view)
		if (!rendererPtr->Render(worldObjectsPtr)) break; 

		//handle all user input
		HandleUserInput(selectedObject);	
	}

	//
	std::cout << "Renderer has been shut down due to an unexpected error. Check above message for details. Force closing in 5 seconds..." << std::endl;
	SDL_Delay(5000); //wait for 5 seconds to allow user to see this error message
}

void StartMe::HandleUserInput(std::unique_ptr<PrimitiveObject>& selectedObject){	
	//transform contains methods relevant for performing linear transformations on objects within the world space
	LinearTransformations transform;

	//check for any user input
	inputHandlerPtr->CheckForInput();

	//handle rotations
	if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput){
		 transform.ApplyRotation(inputHandlerPtr, timePtr, selectedObject);
	}

	//handle translations
	if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput){
		transform.ApplyTransformation(inputHandlerPtr, timePtr, selectedObject);
	}

	//handle switching controller focus
	if (inputHandlerPtr->qInput || inputHandlerPtr->eInput){
		controller->ChangeControllerFocus(worldObjectsPtr, inputHandlerPtr);
		selectedObject = controllerPtr->GetCurrentlyControlledObject();
	}
}