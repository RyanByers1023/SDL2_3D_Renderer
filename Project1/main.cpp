#include <iostream>
#include <vector>
#include <SDL.h>
#include "Screen.h"
#include "Line.h"
#include "vertex.h"
#include "Cube.h"
#include "GlobalCoordinateSystem.h"

int SDL_main(int arg, char* args[]) {
	Screen screen(640, 480); //create the window, make it 640x480 resolution
	vec3 centerOfScreen = { screen.width / 2, screen.height / 2, 0};
	Cube cube(screen, centerOfScreen, 100); //create a 100px x 100px x 100px cube in the center of the screen

	while (true) {
		cube.Draw(); //this adds all of the pixels needed to draw the cube into screen.vertices
		screen.Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
		screen.Clear(); //clear the screen (will also clear out screen.vertices)
		screen.CheckForInput(); //check for user input
		SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Higher framerate = faster simulation speed. I will need to solve this problem later.
	}
	return 0;
}

//use the arrow keys to spin the box around