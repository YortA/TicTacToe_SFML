#include "StateManager.h"

// Default constructor just initializes State (starts as PLAYER, if menu is added we can start with MENU for example)
StateManager::StateManager()
{
	state = new State;
}

// We can change the game state when we want to take turns
StateManager::StateManager(State::GAME_STATE gameState)
{
	state = new State;

	state->gameState = gameState;
}

StateManager::~StateManager()
{
	delete state;
}