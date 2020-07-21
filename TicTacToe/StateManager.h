#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"	// i don't think we need this here.

class StateManager
{
private:
	int playerTurn;
	int currentState;

	// Grab SFML functions to post to screen
	//sf::Sprite

	

public:
	StateManager();
	StateManager(State::GAME_STATE gameState);
	~StateManager();

	class State* state;

};