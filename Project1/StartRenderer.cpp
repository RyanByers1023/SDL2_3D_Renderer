#include "StartRenderer.h"

void StartEngine() {
	Screen screen(1280, 720); //create the window, parameters indicate resolution (width, height)

	ProjectionMatrix projMatrix(screen); //create the projection Matrix using default values

	Cube cube(screen, { 20.0f, 40.0f, 90.0f }, 100); //create a 100px x 100px x 100px cube in the center of the screen. parameters: (Screen object, position to spawn object (vec3), size of cube (int in pixels)

	while (true) {
		screen.CalcDeltaTime(); //calculate the time since the last frame has occured
		//cube.Draw(); //this adds all of the pixels needed to draw the cube into screen.vertices
		screen.Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
		screen.Clear(); //clear the screen (will also clear out screen.vertices)
		screen.CheckForInput(); //check for user input
		SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Higher framerate = faster simulation speed. I will need to solve this problem later.
	}
}