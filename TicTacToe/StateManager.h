#pragma once
#include "State.h"

class StateManager
{
private:
public:
	StateManager();
	~StateManager();

	void create();
	void destroy();

	GAME_STATE* gameState = nullptr;						// GAME_STATE controls whose turn it is, and what's happening in-game.
	UI_STATE* uiState = nullptr;

};