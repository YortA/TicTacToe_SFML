#include "InputManager.h"


InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::update(Entity* entity, State* state)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (state->gameState == State::GAME_STATE::PLAYER)
		{
			entity->setOpacity(45.0);
		}
	}
}