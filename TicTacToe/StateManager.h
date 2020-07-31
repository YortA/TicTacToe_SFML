#pragma once
#include "State.h"

class StateManager
{
private:
public:
	StateManager();
	StateManager(GAME_STATE gameState);			// construct with our game state.
	~StateManager();

	GAME_STATE* gameState;						// GAME_STATE controls whose turn it is, and what's happening in-game.
};