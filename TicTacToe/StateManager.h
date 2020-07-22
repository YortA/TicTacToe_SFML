#pragma once
#include "State.h"

class StateManager
{
private:
public:
	StateManager();
	StateManager(State::GAME_STATE gameState);
	~StateManager();

	class State* state;

};