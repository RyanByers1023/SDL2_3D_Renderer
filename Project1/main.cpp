#include "Renderer.h"
#include "Spawner.h"

int SDL_main(int arg, char* args[]) {
	int screenWidth = 1280, screenHeight = 720; //set screenWidth and screenHeight values, measured in pixels. Determines window size.
	Renderer renderer(screenWidth, screenHeight); //create renderer
	SpawnCube(renderer, "cube1"); //spawner needs access to the renderer and it also needs a unique name for the object to be spawned
	renderer.StartRendering(); //begin rendering
	return 0;
}

//use the arrow keys to spin the box around
//wasd control the position of the box on the x and y axis
//z and x move the box along the z-axis
