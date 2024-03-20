#include <iostream>
#include <vector>
#include <SDL.h>
#include "Screen.h"
#include "Line.h"
#include "vertex.h"
#include "Cube.h"
#include "GlobalCoordinateSystem.h"

int SDL_main(int arg, char* args[]) {
	Screen screen(1280, 720); //create the window, parameters indicate resolution (width, height)
	vec3 centerOfScreen = { screen.width / 2, screen.height / 2, 0}; //store the center of the screen
	Cube cube(screen, centerOfScreen, 100); //create a 100px x 100px x 100px cube in the center of the screen. parameters: (Screen object, position to spawn object (vec3), size of cube (int in pixels))

	while (true) {
		cube.Draw(); //this adds all of the pixels needed to draw the cube into screen.vertices
		screen.Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
		screen.Clear(); //clear the screen (will also clear out screen.vertices)
		screen.CheckForInput(); //check for user input
		SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Higher framerate = faster simulation speed. I will need to solve this problem later.
		//solution to this problem: need time since last update (store as msec since last update as an int, deltaTime) better as float?? i dont know
		//any changes made using frame changes as a unit of time need to be multiplied by deltaTime (i think this is commonly referred to as normalization)
		//possible that it may be efficient to store this value, deltaTime, in screen as an attribute eg. screen.deltaTime.
		//reasoning: screen is passed to mostly everything as this is a required parameter of most if not all of the SDL2 methods i am using, so I may as well store it here if I need such constant access to it
		//this (deltaTime) will have the effect of making both physics calculations and any transformations, rotations, etc. not change their speed when framerate increases (increase in speed) or when the framerate decreases (decrease in speed)
		//the framerate will fluctuate depending on the hardware used to run the simulation. dont want this. deltaTime should solve this dilemma.
	}
	return 0;
}

//use the arrow keys to spin the box around

//NOTE: The next thing I need to do is program a projection matrix. This will involve developement of a function that allows the capability of matrix multiplication
