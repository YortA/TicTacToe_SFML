#include "Clock.h"

Clock::Clock()
{
	clock = new sf::Clock;
}

Clock::~Clock()
{
	delete clock;
}

//
//
//

// Getters
float Clock::getMicroseconds()
{
	return (float)clock->getElapsedTime().asMicroseconds();
}

float Clock::getMilliseconds()
{
	return (float)clock->getElapsedTime().asMilliseconds();
}

float Clock::getSeconds()
{
	return (float)clock->getElapsedTime().asSeconds();
}

// Restart
float Clock::restartMicroseconds()
{
	return (float)clock->restart().asMicroseconds();
}

float Clock::restartMilliseconds()
{
	return (float)clock->restart().asMilliseconds();
}

float Clock::restartSeconds()
{
	return (float)clock->restart().asSeconds();
}