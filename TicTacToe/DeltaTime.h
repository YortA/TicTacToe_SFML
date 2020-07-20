#pragma once

class DeltaTime
{
private:
	enum class TOGGLE
	{
		MICROSECONDS,
		MILLISECONDS,
		SECONDS
	};

	TOGGLE toggle;			// create our toggle enum class inside our class

	class Clock* clock = nullptr;		// point to our clock class 

	float timeElapsed;
	float restart;

public:
	DeltaTime();
	~DeltaTime();

	void update();	// we need to update in order to render

	// Get our private members
	float getTimeElapsed();
	float getRestart();

	// Toggle variable, set our enum to one
	void toggleMicroseconds();
	void toggleMilliseconds();
	void toggleSeconds();
};