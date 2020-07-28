#include "InputManager.h"
#include "StateManager.h"					// so we can use statemanager methods
#include "Entity.h"
#include "Window.h"
#include "SFML/Window/Mouse.hpp"			// for sfml mouse functionality

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

// Check if our mouse is hovering over an entity (no_marker) and if it is, allow a click
// TO DO:
// Check to make sure there's not already an entity in that location
void InputManager::update(Entity* entity, StateManager* statemanager, Window* window)
{   
    // if our mouse is pressed, and it's the player's turn:
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (*statemanager->gameState == GAME_STATE::PLAYER))
    {
        // if the mouse is inside of the entity position
        if ((sf::Mouse::getPosition(*window->getWindow()).x > entity->getLeft()) &&
            (sf::Mouse::getPosition(*window->getWindow()).x < entity->getWidth()) &&
            (sf::Mouse::getPosition(*window->getWindow()).y > entity->getTop()) &&
            (sf::Mouse::getPosition(*window->getWindow()).y < entity->getHeight()))
        {
            if (entity->getOpacity() < 255);
            {
                entity->setOpacity(255);
                entity->setId('X');                             // set our player marker
                *statemanager->gameState = GAME_STATE::AI;
            }
        }
    }
}