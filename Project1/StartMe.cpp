#include "StartMe.h"
 
StartMe::StartMe(int windowWidth, int windowHeight)
   : inputHandlerPtr(std::make_shared<InputHandler>()),
	 controllerPtr(std::make_shared<Controller>(inputHandlerPtr)),
	 timePtr(std::make_shared<Time>()),
	 rendererPtr(std::make_shared<Renderer>(windowWidth, windowHeight)) {}

void StartMe::StartRendering() {
	SpawnCube(rendererPtr->worldObjectsPtr, "cube1"); //spawner needs access to the renderer and it also needs a unique name for the object to be spawned

	while (true) {
		timePtr->Tick(); //calculate the time since the last frame has occured
		inputHandlerPtr->CheckForInput(); //check for user input
		controllerPtr->ChangeControllerFocus(rendererPtr->worldObjectsPtr); //change the selected object (if needed)
		if (!rendererPtr->Render()) break; //this adds all of the pixels needed to draw all shapes in worldObjects vector into screen.vertices

		std::shared_ptr<PrimitiveObject> selectedObject = controllerPtr->GetCurrentlyControlledObject(); //get the currently selected object

		LinearTransformations transform;

		if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput) transform.ApplyRotation(inputHandlerPtr, timePtr, selectedObject);
		if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput) transform.ApplyTransformation(inputHandlerPtr, timePtr, selectedObject);
	}

	std::cout << "Renderer has been shut down due to an unexpected error. Check above message for details. Force closing in 5 seconds..." << std::endl;
	SDL_Delay(5000); //wait for 5 seconds to allow user to see this error message
}