#include "StartMe.h"

StartMe::StartMe(int windowWidth, int windowHeight)
   : inputHandlerPtr(std::make_shared<InputHandler>()), //accessed by StartMe and Controller
	 timePtr(std::make_shared<Time>()), //accessed by StartMe and LinearTransformations
	 worldObjectsPtr(std::make_shared<WorldObjects>()), //accessed by renderer and controller
	 controllerPtr(std::make_unique<Controller>(worldObjectsPtr)), //accessed only by StartMe
	 rendererPtr(std::make_unique<Renderer>(windowWidth, windowHeight, worldObjectsPtr)), //accessed only by StartMe
	 selectedObjectPtr(std::make_shared<PrimitiveObject>()) {} //accessed by controller and linearTransformations, and StartMe 


void StartMe::StartRendering() {
	Spawner spawner;
	
	//spawn a single cube in the world
	spawner.SpawnCube(worldObjectsPtr, "cube1");

	while (true) {
		//calculate the time since the last frame has occured, store this value as deltaTime
		timePtr->Tick(); 

		//check for user input
		inputHandlerPtr->CheckForInput(); 

		//handle user input
		HandleInput();

		//perform rendering, if an error occurs within the rendering pipeline, break this loop
		if (!rendererPtr->Render(worldObjectsPtr)) break; 
	}

	std::cout << "Renderer has been shut down due to an unexpected error. Check above message for details. Force closing in 5 seconds..." << std::endl;
	SDL_Delay(5000); //wait for 5 seconds to allow user to see this error message
}

void StartMe::HandleInput(){
	//LinearTransformations object created to access linear transformation methods
	LinearTransformations transform;

	//handle input relevant to linear transformations
	if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput) transform.ApplyRotation(inputHandlerPtr, timePtr, selectedObjectPtr);
	if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput) transform.ApplyTransformation(inputHandlerPtr, timePtr, selectedObjectPtr);

	//handle input relevant to object controller
	if(inputHandlerPtr->qInput || inputHandlerPtr->eInput) controllerPtr->ChangeControllerFocus(inputHandlerPtr, worldObjectsPtr); 

	//get the currently selected object
	std::shared_ptr<PrimitiveObject> selectedObjectPtr = controllerPtr->GetCurrentlyControlledObject(); 
}