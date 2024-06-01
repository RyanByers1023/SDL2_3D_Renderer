#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>

class Screen {
private:
	SDL_Window* window;
	SDL_Renderer* SDLRenderer;
	std::vector<SDL_FPoint> vertices;	
public:
	Screen(int screenWidth, int screenHeight); //initialize SDL_VIDEO, create window and renderer, and set scale of renderer
	void CreatePixel(float x, float y); //enter new vertex into vertices vector
	void CreatePixel(Vec2 newPixel);
	void Show(); //display pixels to screen (will also clear the screen before conducting this operation)
	void Clear(); //clear vertices vector
	int width; //width of screen in pixels
	int height; //height of screen in pixels
};