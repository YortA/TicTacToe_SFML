#include "InputManager.h"
#include "StateManager.h"					// so we can use statemanager methods
#include "Entity.h"
#include "Window.h"
#include "SFML/Window/Mouse.hpp"			// for sfml mouse functionality
#include "SFML/Window/Keyboard.hpp"	
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->getWindow()->close();
    }

    if (*statemanager->uiState == UI_STATE::TITLE)
    {
        if (clickedOnEntity(entity, window))
        {
            *statemanager->uiState = UI_STATE::MAIN;
        }
    }

    else if (*statemanager->uiState == UI_STATE::MAIN)
    {
        if (clickedOnEntity(entity, window))
        {
            if (entity->getMenuID() == 'R')
            {
                // will do soon (restart board)
            }
            else if (entity->getMenuID() == 'Q')
            {
                *statemanager->uiState = UI_STATE::TITLE;       // returns to title screen
            }
        }
    }

    // if our mouse is pressed, and it's the player's turn:
    if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (*statemanager->gameState == GAME_STATE::PLAYER))
    {
        // if the mouse is inside of the entity position
        if ((sf::Mouse::getPosition(*window->getWindow()).x > entity->getLeft()) &&
            (sf::Mouse::getPosition(*window->getWindow()).x < entity->getWidth()) &&
            (sf::Mouse::getPosition(*window->getWindow()).y > entity->getTop()) &&
            (sf::Mouse::getPosition(*window->getWindow()).y < entity->getHeight()))
        {
            if ((entity->getOpacity() < 255) && (*statemanager->uiState == UI_STATE::MAIN))
            {
                debugger->my_debug_timer("InputManager() function called.");    // timestamps for console
                soundPop2->play();
                entity->setOpacity(255);
                entity->setId('X');                                             // set our player marker
                std::cout << entity->getId() << std::endl;
                *statemanager->gameState = GAME_STATE::AI;                      // gamestate back to AI
            }
        }
    }
}

bool InputManager::clickedOnEntity(Entity* entity, Window* window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        (sf::Mouse::getPosition(*window->getWindow()).x > entity->getLeft()) &&
        (sf::Mouse::getPosition(*window->getWindow()).x < entity->getWidth()) &&
        (sf::Mouse::getPosition(*window->getWindow()).y > entity->getTop()) &&
        (sf::Mouse::getPosition(*window->getWindow()).y < entity->getHeight()))
    {
        return true;
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