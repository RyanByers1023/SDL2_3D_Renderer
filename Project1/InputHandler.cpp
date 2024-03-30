#include "InputHandler.h"

void InputHandler::CheckForInput() { 
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			SDL_Quit();
			exit(0);
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
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
			case SDLK_z:
				zInput = true;
				break;
			case SDLK_x:
				xInput = true;
				break;
			}


		}
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
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
			}
		}
	}
}