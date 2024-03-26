#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>

class Screen {
private:
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<SDL_FPoint> vertices;
	std::chrono::milliseconds prevTime;
public:
	Screen(int screenWidth, int screenHeight); //initialize SDL_VIDEO, create window and renderer, and set scale of renderer
	void CreatePixel(float x, float y); //enter new vertex into vertices vector
	void Show(); //display pixels to screen (will also clear the screen before conducting this operation)
	void Clear(); //clear vertices vector
	void CheckForInput(); //check for user input
	void CalcDeltaTime(); //calulate the time since the last frame
	int width;
	int height;

	bool leftInput = false;
	bool rightInput = false;
	bool upInput = false;
	bool downInput = false;

	bool wInput = false;
	bool aInput = false;
	bool sInput = false;
	bool dInput = false;
	
	std::chrono::milliseconds deltaTime;
};