#pragma once

#include <SDL.h>
#include <vector>
using namespace std;


class Rectangle {
public:
	int l;
	int h;
	SDL_Point center;
	Rectangle(int l, int h, SDL_Point pos);
	void Draw(SDL_Renderer* renderer);
private:
	vector<SDL_Point> pointVector;
};