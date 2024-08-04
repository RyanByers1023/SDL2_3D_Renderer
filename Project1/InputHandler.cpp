#include "InputHandler.h"

void InputHandler::CheckForInput() { 
	SDL_Event event;	
	while (SDL_PollEvent(&event)) { //check for any event
		if (event.type == SDL_QUIT) { //program exit event (pressed red "x" button)
			SDL_Quit();
			exit(0);
		}
		if (event.type == SDL_KEYDOWN) { //key depress event
			HandleKeyDown(event);
		}
		if (event.type == SDL_KEYUP) { //key up event
			HandleKeyUp(event);
		}
	}
}

void InputHandler::HandleKeyDown(const SDL_Event& event) {
	switch (event.key.keysym.sym) { //switch used to determine which key has been pressed
		//arrow keys
	case SDLK_LEFT:
		leftInput = true;
		break;
	case SDLK_RIGHT:
		rightInput = true;
		break;
	case SDLK_UP:
		upInput = true;
		break;
	case SDLK_DOWN:
		downInput = true;
		break;

		//WASD keys (XY plane movement)
	case SDLK_w:
		wInput = true;
		break;
	case SDLK_a:
		aInput = true;
		break;
	case SDLK_s:
		sInput = true;
		break;
	case SDLK_d:
		dInput = true;
		break;

		//Rotation keys Z/X
	case SDLK_z:
		zInput = true;
		break;
	case SDLK_x:
		xInput = true;
		break;

		//Scaling keys Q/E
	case SDLK_q:
		qInput = true;
		break;
	case SDLK_e:
		eInput = true;
		break;

		//+/- keys Z plane movement
	case SDLK_MINUS:
		minusInput = true;
		break;
	case SDLK_PLUS:
		plusInput = true;
		break;
	}
}

void InputHandler::HandleKeyUp(const SDL_Event& event){
	switch (event.key.keysym.sym) { //switch used to determine which key was undepressed
	case SDLK_LEFT:
		leftInput = false;
		break;
	case SDLK_RIGHT:
		rightInput = false;
		break;
	case SDLK_UP:
		upInput = false;
		break;
	case SDLK_DOWN:
		downInput = false;
		break;

	case SDLK_w:
		wInput = false;
		break;
	case SDLK_a:
		aInput = false;
		break;
	case SDLK_s:
		sInput = false;
		break;
	case SDLK_d:
		dInput = false;
		break;
	case SDLK_z:
		zInput = false;
		break;
	case SDLK_x:
		xInput = false;
		break;
	case SDLK_q:
		qInput = false;
		break;
	case SDLK_e:
		eInput = false;
		break;
	case SDLK_MINUS:
		minusInput = false;
		break;
	case SDLK_PLUS:
		plusInput = false;
		break;
	}
}