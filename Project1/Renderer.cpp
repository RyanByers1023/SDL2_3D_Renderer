#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight) {
	this->screenPtr = new Screen(windowWidth, windowHeight);
	this->projMatrixPtr = new ProjectionMatrix(windowWidth, windowHeight);
	this->inputHandlerPtr = new InputHandler();
	this->timePtr = new Time();
}

Renderer::~Renderer() {
	delete this->screenPtr;
	delete this->projMatrixPtr;
	delete this->inputHandlerPtr;
	delete this->timePtr;
}

void Renderer::StartRendering() {
	while (true) {
		timePtr->Tick(); //calculate the time since the last frame has occured
		inputHandlerPtr->CheckForInput(); //check for user input
		if (!Render()) break; //this adds all of the pixels needed to draw all shapes in worldObjects vector into screen.vertices
		screenPtr->Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
		screenPtr->Clear(); //clear the screen (will also clear out screen.vertices)
		SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Is normalized using Time.deltaTime;
	}

	std::cout << "Renderer has been shut down due to an error. Check above message for reason. Closing in 5 seconds..." << std::endl;
	SDL_Delay(5000); //wait for 5 seconds
}

bool Renderer::Render() { //draws all objects contained within worldObjects to the screen
	if (worldObjects.empty()) {
		std::cout << "There are no objects to render. Renderer shutting down..." << std::endl;
		return false;
	}

	for (const auto& it : worldObjects) {
		for (auto& tri : it.second.primitiveMesh.triangles) {
			triangle projectedTriangle;

			for (int i = 0; i < 3; i++) {
				projectedTriangle.p[i] = tri.p[i] * *projMatrixPtr;
			}

			projectedTriangle.p[0].x += 1.0f; projectedTriangle.p[0].y += 1.0f;
			projectedTriangle.p[1].x += 1.0f; projectedTriangle.p[1].y += 1.0f;
			projectedTriangle.p[2].x += 1.0f; projectedTriangle.p[2].y += 1.0f;

			float halfScreenWidth = static_cast<float>(screenPtr->width) * 0.5f;
			float halfScreenHeight = static_cast<float>(screenPtr->height) * 0.5f;

			projectedTriangle.p[0].x *= halfScreenWidth;
			projectedTriangle.p[0].y *= halfScreenHeight;
			projectedTriangle.p[1].x *= halfScreenWidth;
			projectedTriangle.p[1].y *= halfScreenHeight;
			projectedTriangle.p[2].x *= halfScreenWidth;
			projectedTriangle.p[2].y *= halfScreenHeight;

			float x1 = projectedTriangle.p[0].x;
			float y1 = projectedTriangle.p[0].y;

			float x2 = projectedTriangle.p[1].x;
			float y2 = projectedTriangle.p[1].y;

			float x3 = projectedTriangle.p[2].x;
			float y3 = projectedTriangle.p[2].y;

			Line line1(*screenPtr, x1, y1, x2, y2); //first line of triangle (side a)
			line1.Draw();

			Line line2(*screenPtr, x2, y2, x3, y3); //second line of triangle (side b)
			line2.Draw();

			Line line3(*screenPtr, x3, y3, x1, y1); //third line of triangle (side c) -- this is the hypotenuse
			line3.Draw();
		}
	}

	LinearTransformations transform;

	if (inputHandlerPtr->leftInput || inputHandlerPtr->rightInput || inputHandlerPtr->upInput || inputHandlerPtr->downInput) transform.ApplyRotation(inputHandlerPtr, timePtr, worldObjects["cube1"]); //this will be changed later on to be generalized. Can pick and choose which shape to modify
	if (inputHandlerPtr->wInput || inputHandlerPtr->aInput || inputHandlerPtr->sInput || inputHandlerPtr->dInput || inputHandlerPtr->zInput || inputHandlerPtr->xInput) transform.ApplyTransformation(inputHandlerPtr, timePtr, worldObjects["cube1"]);

	return true;
}
