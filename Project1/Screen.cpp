#include "Screen.h"

Screen::Screen(int screenWidth, int screenHeight) {
	this->width = screenWidth;
	this->height = screenHeight;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("SDL2 3-D Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	prevTime = std::chrono::high_resolution_clock::now(); //intialize prevTime for first deltaTime calculation	
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

void Screen::CheckForInput() { //move to seperate class
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

//need time since last update (store as msec since last update as a float, deltaTime)
//any changes made using frame changes as a unit of time need to be multiplied by deltaTime (i think this is commonly referred to as normalization)
//possible that it may be efficient to store this value, deltaTime, in screen as an attribute eg. screen.deltaTime.
//reasoning: screen is passed to mostly everything as this is a required parameter of most if not all of the SDL2 methods i am using, so I may as well store it here if I need such constant access to it
//this (deltaTime) will have the effect of making both physics calculations and any transformations, rotations, etc. not change their speed when framerate increases (increase in speed) or when the framerate decreases (decrease in speed)
//the framerate will fluctuate depending on the hardware used to run the simulation. dont want this. deltaTime should solve this dilemma.

void Screen::CalcDeltaTime() { //move to seperate class
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::steady_clock::time_point TimePoint;

	TimePoint currTime = Time::now(); //get the current time
	std::chrono::duration<float> deltaTimeInSeconds = currTime - prevTime; //calculate the time since the last time this code was executed (last frame)
	prevTime = currTime; //make the prevTime msec value = to the current time for use in the next iteration

	this->deltaTime = deltaTimeInSeconds.count();
}

