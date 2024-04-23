#include "StartMe.h"

StartMe::StartMe(int windowWidth, int windowHeight) {
	this->inputHandlerPtr = new InputHandler();
	this->timePtr = new Time();
	this->worldObjectsPtr = new WorldObjects();
	this->controllerPtr = new Controller(inputHandlerPtr, worldObjectsPtr);
	this->rendererPtr = new Renderer(windowWidth, windowHeight, worldObjectsPtr);
}

StartMe::~StartMe(){
	delete this->inputHandlerPtr;
	delete this->timePtr;
	delete this->worldObjectsPtr;
	delete this->controllerPtr;
}

void StartMe::StartRendering() {
	SpawnCube(worldObjectsPtr, "cube1"); //spawner needs access to the renderer and it also needs a unique name for the object to be spawned
	SpawnCube(worldObjectsPtr, "cube2");
	SpawnCube(worldObjectsPtr, "cube3");

	while (true) {
		timePtr->Tick(); //calculate the time since the last frame has occured
		inputHandlerPtr->CheckForInput(); //check for user input
		controllerPtr->ChangeControllerFocus(); //change the selected object (if needed)
		if (!rendererPtr->Render()) break; //this adds all of the pixels needed to draw all shapes in worldObjects vector into screen.vertices

		PrimitiveObject* selectedObject = controllerPtr->GetCurrentlyControlledObject(); //get the currently selected object

		LinearTransformations transform;

		if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput) transform.ApplyRotation(inputHandlerPtr, timePtr, *selectedObject);
		if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput) transform.ApplyTransformation(inputHandlerPtr, timePtr, *selectedObject);
		//if (inputHandlerPtr->minusInput || inputHandlerPtr->plusInput) transform.ApplyScaling(inputHandlerPtr, *selectedObject, timePtr);
	}

	std::cout << "Renderer has been shut down due to an error. Check above message for reason. Closing in 5 seconds..." << std::endl;
	SDL_Delay(5000); //wait for 5 seconds
}