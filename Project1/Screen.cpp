#include "Screen.h"

Screen::Screen(const int screenWidth, const int screenHeight)
	: width(screenWidth),
	  height(screenHeight),
	  window(SDL_CreateWindow("SDL2 3-D Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)),
	  SDLRenderer(SDL_CreateRenderer(window, -1, 0))
	   
{
	SDL_Init(SDL_INIT_VIDEO);
}


void Screen::CreatePixel(const float x, const float y) {
	Vec2 newPoint = { x, y };
	vertices.push_back(newPoint); //create new SDL_FPoint object and push to vertices vector
}

void Screen::CreatePixel(const Vec2& newPoint){
	vertices.push_back(newPoint);
}

void Screen::Show() const {
	SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255); //set color to black
	SDL_RenderClear(SDLRenderer);

	SDL_SetRenderDrawColor(SDLRenderer, 255, 255, 255, 255); //set color to white
	for (auto& vertex : vertices) { //draw all of the vertices within the vector vertices to the screen
		SDL_RenderDrawPointF(SDLRenderer, vertex.x, vertex.y);
	}

	SDL_RenderPresent(SDLRenderer); //present drawn vertices to the screen
}

void Screen::Clear() {
	vertices.clear();
}



