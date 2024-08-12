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
	~StartMe();
	void StartRendering();
private:
	std::unique_ptr<InputHandler> inputHandlerPtr;
	std::unique_ptr<Time> timePtr;
	Controller* controllerPtr;
	WorldObjects* worldObjectsPtr;
	Renderer* rendererPtr;
};
