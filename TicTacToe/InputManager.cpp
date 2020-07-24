#include "InputManager.h"
#include "StateManager.h"					// so we can use statemanager methods
#include "Entity.h"
#include "SFML/Window/Mouse.hpp"			// for sfml mouse functionality

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

// TO DO:
// Check bounds of mouse (inside window parameters)
// Check bounds of mouse (inside entity parameters)
void InputManager::update(class Entity* entity, class StateManager* statemanager, class Window* window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (statemanager->state->gameState == State::GAME_STATE::PLAYER)
		{
			//entity->setOpacity(45.0);
		}
	}
}

