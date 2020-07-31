#pragma once

// SEE https://www.sfml-dev.org/tutorials/2.5/system-time.php
// for more info on how time works in sfml

#include "SFML/System/Clock.hpp"	// SFML built-in clock lib

class Clock
{
private:
	sf::Clock* clock = nullptr;			// calling the sfml clock* object to be used inside our clock class

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