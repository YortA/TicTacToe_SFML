#pragma once
#include "State.h"

class StateManager
{
private:
public:
	StateManager();
	StateManager(GAME_STATE gameState);
	~StateManager();

	GAME_STATE* gameState;

};