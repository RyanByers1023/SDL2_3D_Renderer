#include "Rectangle.h"


Rectangle::Rectangle(int length, int height, SDL_Point pos) {
	this->l = length;
	this->h = height;
	this->center = pos;

	float halfL = l * 0.5;
	float halfH = h * 0.5;

	SDL_Point bottomLeft = { center.x - halfL, center.y + halfH };
	SDL_Point bottomRight = { center.x + halfL, center.y + halfH };
	SDL_Point topRight = { center.x + halfL, center.y - halfH };
	SDL_Point topLeft = { center.x - halfL, center.y - halfH };

	pointVector.push_back(bottomLeft);
	pointVector.push_back(bottomRight);
	pointVector.push_back(topRight);
	pointVector.push_back(topLeft);
	pointVector.push_back(bottomLeft);
}

void Rectangle::Draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLines(renderer, pointVector.data(), pointVector.size());
}