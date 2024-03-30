#include "Time.h"

Time::Time() {
	prevTime = std::chrono::high_resolution_clock::now(); //intialize prevTime for first deltaTime calculation
}

void Time::Tick() {
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::steady_clock::time_point TimePoint;

	TimePoint currTime = Time::now(); //get the current time
	std::chrono::duration<float> deltaTimeInSeconds = currTime - prevTime; //calculate the time since the last time this code was executed (last frame)
	prevTime = currTime; //make the prevTime msec value = to the current time for use in the next iteration

	this->deltaTime = deltaTimeInSeconds.count();
}