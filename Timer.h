#pragma once

#include<SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Timer {
private:

	Clock clock;
	Clock restartClock;
	Time time;

public:

	Timer();
	~Timer();

	void Update();
	
};

namespace timesec {
	extern float timeScale;
	extern float deltaTime;
}