#pragma once
#include "SFML/Graphics.hpp"

class StateManager
{
private:
	int playerTurn;
	int currentState;

	// Grab SFML functions to post to screen
	//sf::Sprite

	enum class STATE
	{
		START,		// start == 0
		PLAYING,
		GAMEOVER
	};

public:
	STATE state;
};