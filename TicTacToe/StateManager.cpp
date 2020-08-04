#include "StateManager.h"

// Default constructor just initializes State (starts as PLAYER, if menu is added we can start with MENU for example)
StateManager::StateManager()
{
    create();
}

StateManager::~StateManager()
{
    destroy();
}

void StateManager::create()
{
    gameState = new GAME_STATE;
    uiState = new UI_STATE;
}

void StateManager::destroy()
{
    delete gameState;
    delete uiState;
}
