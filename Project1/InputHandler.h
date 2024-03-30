#pragma once
#include "SDL.h"

class InputHandler {
public:
	//public methods:
	void CheckForInput();
	//public input flags:
	bool leftInput = false;
	bool rightInput = false;
	bool upInput = false;
	bool downInput = false;

	bool wInput = false;
	bool aInput = false;
	bool sInput = false;
	bool dInput = false;
	bool zInput = false;
	bool xInput = false;

private:
	//private attributes:
	SDL_Event event;
};
