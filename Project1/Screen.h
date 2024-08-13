#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>
#include "Vec2.h"

class Screen {
public:
	Screen(const int screenWidth, const int screenHeight); //initialize SDL_VIDEO, create window and renderer, and set scale of renderer
	void CreatePixel(const float x, const float y); //enter new vertex into vertices vector
	void CreatePixel(const Vec2& newPixel);
	void Show() const; //display pixels to screen (will also clear the screen before conducting this operation)
	void Clear(); //clear vertices vector
	int width; //width of screen in pixels
	int height; //height of screen in pixels
private:
	SDL_Window* window;
	SDL_Renderer* SDLRenderer;
	std::vector<Vec2> vertices;	
};