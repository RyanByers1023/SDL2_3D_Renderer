#include "StartMe.h"

StartMe::StartMe(const int& windowWidth, const int& windowHeight)
   : inputHandlerPtr(std::make_unique<InputHandler>()), //accessed by StartMe, LinearTransformations, and Controller
	 timePtr(std::make_unique<Time>()), //accessed by StartMe and LinearTransformations (passed by reference)
	 worldObjectsPtr(std::make_unique<WorldObjects>()), //accessed by renderer, spawner, and controller (passed by reference)
	 controllerPtr(std::make_unique<Controller>()), //accessed only by StartMe
	 rendererPtr(std::make_unique<Renderer>(windowWidth, windowHeight)), //accessed only by StartMe
	 selectedObjectPtr(std::make_shared<PrimitiveObject>()) {} //accessed by controller and linearTransformations, and StartMe 


void StartMe::StartRendering() {
	Spawner spawner; //create for access to spawn functions
	
	//spawn a single cube in the world
	spawner.SpawnCube(worldObjectsPtr, "cube1"); //pass by reference

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

	//handle input relevant to rotations
	if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput){
		transform.ApplyRotation(inputHandlerPtr, timePtr, selectedObjectPtr);
	} 

	//handle input relevant to linear transformations
	if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput){
		transform.ApplyTransformation(inputHandlerPtr, timePtr, selectedObjectPtr);
	} 

	//handle input relevant to object controller
	if(inputHandlerPtr->qInput || inputHandlerPtr->eInput){
		selectedObjectPtr = controllerPtr->ChangeControllerFocus(inputHandlerPtr, worldObjectsPtr); 
	} 

}