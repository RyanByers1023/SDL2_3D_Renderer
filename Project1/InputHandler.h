#pragma once
#include "SDL.h"

class InputHandler {
public:
	//default constructor:
	InputHandler() : leftInput(false), rightInput(false), upInput(false), downInput(false), wInput(false), aInput(false), sInput(false), dInput(false), zInput(false), xInput(false), qInput(false), eInput(false), minusInput(false), plusInput(false) {};

	//public methods:
	void CheckForInput();

	//input flags:

	//arrow keys:
	bool leftInput;
	bool rightInput;
	bool upInput;
	bool downInput;

	//wasd keys:
	bool wInput;
	bool aInput;
	bool sInput;
	bool dInput;

	//extra controls:
	bool zInput;
	bool xInput;
	bool qInput;
	bool eInput;
	bool minusInput;
	bool plusInput;

	//note: not getting specific in comments regarding keys' functionalities here b/c they most likely will change thorughout development

private:
	//private methods:
	void HandleKeyDown(const SDL_Event& event);
	void HandleKeyUp(const SDL_Event& event);
};
