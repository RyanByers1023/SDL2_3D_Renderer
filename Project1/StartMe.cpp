#include "StartMe.h"

//FIX-ME: initialize selectedObject/controllerPtr

StartMe::StartMe(int windowWidth, int windowHeight) {
	inputHandlerPtr = std::make_unique<InputHandler>();
	timePtr = std::make_unique<Time>();
	worldObjectsPtr = std::make_unique<WorldObjects>();
	this->controllerPtr = new Controller();
	this->rendererPtr = new Renderer(windowWidth, windowHeight);
}

StartMe::~StartMe(){
	delete this->controllerPtr;
}

void StartMe::StartRendering() {
	SpawnCube(worldObjectsPtr, "cube1"); //spawner needs access to the renderer and it also needs a unique name for the object to be spawned
	controllerPtr->InitializeIterator(worldObjectsPtr);

	while (true) {
		timePtr->Tick(); //calculate the time since the last frame has occured
		inputHandlerPtr->CheckForInput(); //check for user input
		controllerPtr->ChangeControllerFocus(worldObjectsPtr, inputHandlerPtr); //change the selected object (if needed)
		if (!rendererPtr->Render(worldObjectsPtr)) break; //this adds all of the pixels needed to draw all shapes in worldObjects vector into screen.vertices

		PrimitiveObject* selectedObject = controllerPtr->GetCurrentlyControlledObject(); //get the currently selected object

		LinearTransformations transform;

		if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput) transform.ApplyRotation(inputHandlerPtr, timePtr, selectedObject);
		if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput) transform.ApplyTransformation(inputHandlerPtr, timePtr, selectedObject);
	}

	std::cout << "Renderer has been shut down due to an unexpected error. Check above message for details. Force closing in 5 seconds..." << std::endl;
	SDL_Delay(5000); //wait for 5 seconds to allow user to see this error message
}