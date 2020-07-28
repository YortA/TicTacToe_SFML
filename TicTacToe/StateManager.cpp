#include "StateManager.h"

// Default constructor just initializes State (starts as PLAYER, if menu is added we can start with MENU for example)
StateManager::StateManager()
{
    gameState = new GAME_STATE;
}

// We can change the game state when we want to take turns
StateManager::StateManager(GAME_STATE gameState)
{
    this->gameState = new GAME_STATE;

    *this->gameState = gameState;
}

StateManager::~StateManager()
{
    delete gameState;
}