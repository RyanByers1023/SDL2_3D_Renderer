#include "Screen.h"

Screen::Screen(int screenWidth, int screenHeight) {
	this->width = screenWidth;
	this->height = screenHeight;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "SDL2 3-D Graphics Test");
	SDL_RenderSetScale(renderer, 2, 2);
}

void Screen::CreatePixel(float x, float y) {
	SDL_FPoint newPoint = { x, y };
	vertices.push_back(newPoint); //create new SDL_FPoint object and push to vertices vector
}

void Screen::Show() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //set color to black
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //set color to white
	for (auto& vertex : vertices) { //draw all of the vertices within the vector vertices to the screen
		SDL_RenderDrawPointF(renderer, vertex.x, vertex.y);
	}

	SDL_RenderPresent(renderer); //present drawn vertices to the screen
}

void Screen::Clear() {
	vertices.clear();
}

void Screen::CheckForInput() {
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
			}
		}
	}
}

