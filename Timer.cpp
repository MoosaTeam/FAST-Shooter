#include "Timer.h"

namespace timesec {
	float deltaTime = 0;
	float timeScale = 1;
}

// constructor
Timer::Timer()
{
}

// updates timer
void Timer::Update() {
	time = restartClock.restart();	//Set the deltaTime value on each frame
	timesec::deltaTime = time.asSeconds() * timesec::timeScale;
}

// destructor
Timer::~Timer()
{
}