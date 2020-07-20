#pragma once

#include "SFML/System/Clock.hpp"	// SFML built-in clock lib

class Clock
{
private:
	sf::Clock* clock = nullptr;

public:
	Clock();
	~Clock();

	float getMicroseconds();
	float getMilliseconds();
	float getSeconds();

	float restartMicroseconds();
	float restartMilliseconds();
	float restartSeconds();
};