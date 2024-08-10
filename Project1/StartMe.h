#pragma once
#include "Time.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "WorldObjects.h"
#include "LinearTransformations.h"
#include "Spawner.h"
#include "Controller.h"
#include <memory>

class StartMe {
public:
	StartMe(int windowWidth = 1280, int windowHeight = 720);
	void StartRendering();
private:
	//pointers
	std::unique_ptr<InputHandler> inputHandlerPtr;
	std::unique_ptr<Controller> controllerPtr;
	std::unique_ptr<Time> timePtr;
	std::unique_ptr<WorldObjects> worldObjectsPtr;
	std::unique_ptr<Renderer> rendererPtr;
};
