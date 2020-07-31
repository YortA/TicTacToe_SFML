#pragma once

// SEE https://www.sfml-dev.org/tutorials/2.5/system-time.php
// for more info on how time works in sfml

class DeltaTime
{
private:
	enum class TOGGLE
	{
		MICROSECONDS,
		MILLISECONDS,
		SECONDS
	};

	TOGGLE toggle;						// create our toggle enum class object

	class Clock* clock = nullptr;		// point to our clock class 

	float timeElapsed;
	float restart;

public:
	DeltaTime();
	~DeltaTime();

	void update();	// we need to update in order to render

	// get our private members
	float getTimeElapsed();
	float getRestart();

	// toggle variable, set our enum to one
	void toggleMicroseconds();
	void toggleMilliseconds();
	void toggleSeconds();
};