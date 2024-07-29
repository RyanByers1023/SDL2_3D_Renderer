#pragma once
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
	~StartMe();
	void StartRendering();
private:
	InputHandler* inputHandlerPtr;
	Controller* controllerPtr;
	Time* timePtr;
	WorldObjects* worldObjectsPtr;
	Renderer* rendererPtr;
};
