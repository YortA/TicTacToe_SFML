#include "InputManager.h"
#include "StateManager.h"					// so we can use statemanager methods
#include "Entity.h"
#include "Window.h"
#include "SFML/Window/Mouse.hpp"			// for sfml mouse functionality
#include "Sound.h"

#include "MYDEBUGHELPER.h"

InputManager::InputManager()
{
    soundPop2 = new Sound("Sounds/pop_2.wav");
}

InputManager::~InputManager()
{
    delete soundPop2;
}

// Check if our mouse is hovering over an entity (no_marker) and if it is, allow a click
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
                debugger->my_debug_timer("InputManager() function called.");    // timestamps for console
                soundPop2->play();
                entity->setOpacity(255);
                entity->setId('X');                                             // set our player marker
                *statemanager->gameState = GAME_STATE::AI;                      // gamestate back to AI
            }
        }
    }
}

// check to see if we clicked down on our mouse (left)
bool InputManager::DidMouseTrigger()
{
    bool isDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (isDown != mouseState)
    {
        mouseState = isDown;
        return isDown;
    }
    return false;
}