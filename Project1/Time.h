#pragma once
#include <chrono>

//need time since last update (store as msec since last update as a float, deltaTime)
//any changes made using frame changes as a unit of time need to be multiplied by deltaTime (i think this is commonly referred to as normalization)
//possible that it may be efficient to store this value, deltaTime, in screen as an attribute eg. screen.deltaTime.
//reasoning: screen is passed to mostly everything as this is a required parameter of most if not all of the SDL2 methods i am using, so I may as well store it here if I need such constant access to it
//this (deltaTime) will have the effect of making both physics calculations and any transformations, rotations, etc. not change their speed when framerate increases (increase in speed) or when the framerate decreases (decrease in speed)
//the framerate will fluctuate depending on the hardware used to run the simulation. dont want this. deltaTime should solve this dilemma.

class Time {
public:
	//default contructor
	Time();

	//public methods:
	void Tick(); //calulate the time since the last frame

	//public attributes
	float deltaTime = 0.0f; //time since last frame (float in seconds) Multiply this value by any animations/frame by frame changes to make them frame independent

private:
	//private attributes:
	std::chrono::steady_clock::time_point prevTime; //the time measured as the current time in the last frame. Subtracted from the current time in the current frame to net the time since the last fram (deltaTime)
};
