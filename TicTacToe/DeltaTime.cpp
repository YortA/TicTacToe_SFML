#include "DeltaTime.h"
#include "Clock.h"


DeltaTime::DeltaTime()
	: toggle(TOGGLE::SECONDS),
	timeElapsed(0.0f),
	restart(0.0f)
{
	clock = new Clock;
}

DeltaTime::~DeltaTime()
{
	delete clock;
}

//
//
//

// Update functions
void DeltaTime::update()
{
	switch (toggle)
	{
	case TOGGLE::MICROSECONDS:
		timeElapsed += clock->getMicroseconds();
		restart = clock->restartMicroseconds();
		break;

	case TOGGLE::MILLISECONDS:
		timeElapsed += clock->getMilliseconds();
		restart = clock->restartMilliseconds();
		break;

	case TOGGLE::SECONDS:
		timeElapsed += clock->getSeconds();
		restart = clock->restartSeconds();
		break;
	}
}

// Get functions
float DeltaTime::getTimeElapsed()
{
	return timeElapsed;
}

float DeltaTime::getRestart()
{
	return restart;
}

// Toggle functions
void DeltaTime::toggleMicroseconds()
{
	toggle = TOGGLE::MICROSECONDS;
}

void DeltaTime::toggleMilliseconds()
{
	toggle = TOGGLE::MILLISECONDS;
}

void DeltaTime::toggleSeconds()
{
	toggle = TOGGLE::SECONDS;
}