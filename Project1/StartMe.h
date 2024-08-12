#pragma once
#include <memory>
#include "Time.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "WorldObjects.h"
#include "LinearTransformations.h"
#include "Spawner.h"
#include "Controller.h"

class StartMe {
public:
	StartMe(int windowWidth = 1280, int windowHeight = 720);
	void StartRendering();
private:
	std::shared_ptr<InputHandler> inputHandlerPtr;
	std::shared_ptr<Controller> controllerPtr;
	std::shared_ptr<Time> timePtr;
	std::shared_ptr<Renderer> rendererPtr;
};
