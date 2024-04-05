#include "StartMe.h"

int SDL_main(int arg, char* args[]) {
	StartMe programHandler;
	programHandler.StartRendering();
	return 0;
}

//use the arrow keys to spin the box around
//wasd control the position of the box on the x and y axis
//z and x move the box along the z-axis
