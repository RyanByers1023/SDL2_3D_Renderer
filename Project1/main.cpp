#include <iostream>
#include <vector>
#include <SDL.h>
#include "Screen.h"
#include "Line.h"
#include "vertex.h"
#include "Cube.h"
#include "Matrix.h"

int SDL_main(int arg, char* args[]) {
	Screen screen(1280, 720); //create the window, parameters indicate resolution (width, height)
	vec3 centerOfScreen = { screen.width / 2, screen.height / 2, 0}; //store the center of the screen
	Cube cube(screen, centerOfScreen, 100); //create a 100px x 100px x 100px cube in the center of the screen. parameters: (Screen object, position to spawn object (vec3), size of cube (int in pixels))

	//projection matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
	float fAspectRation = screen.height / screen.width;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	Matrix matProj;

	matProj.matrix[0][0] = fAspectRation * fFovRad;
	matProj.matrix[1][1] = fFovRad;
	matProj.matrix[2][2] = fFar / (fFar - fNear);
	matProj.matrix[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.matrix[2][3] = 1.0f;
	matProj.matrix[3][3] = 0.0f;

	while (true) {
		screen.CalcDeltaTime(); //calculate the time since the last frame has occured
		cube.Draw(); //this adds all of the pixels needed to draw the cube into screen.vertices
		screen.Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
		screen.Clear(); //clear the screen (will also clear out screen.vertices)
		screen.CheckForInput(); //check for user input
		SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Higher framerate = faster simulation speed. I will need to solve this problem later.
	}
	return 0;
}

//use the arrow keys to spin the box around

//NOTE: The next thing I need to do is program a projection matrix. This will involve developement of a function that allows the capability of matrix multiplication
