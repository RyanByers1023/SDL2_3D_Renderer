#pragma once
#include "SDL.h"

class InputHandler {
public:
	//public methods:
	void CheckForInput();
	//input flags:
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
	bool qInput = false;
	bool eInput = false;
	bool minusInput = false;
	bool plusInput = false;

private:
	//private attributes:
	SDL_Event event;
	//private methods:
	void HandleKeyDown(SDL_Event event);
	void HandleKeyUp(SDL_Event event);
};
