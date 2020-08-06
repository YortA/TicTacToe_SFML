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

    //else if (*statemanager->uiState == UI_STATE::MAIN)
    //{
    //    if (clickedOnEntity(entity, window))
    //    {
    //        if (entity->getMenuID() == charRestart)
    //        {
    //            //window->setIsRestarting(true);
    //        }
    //        else if (entity->getMenuID() == charQuit)
    //        {
    //            *statemanager->uiState = UI_STATE::TITLE;       // returns to title screen
    //        }
    //    }
    //}

    // if our mouse is pressed, and it's the player's turn:
    if ((*statemanager->gameState == GAME_STATE::PLAYER))
    {
        // if the mouse is inside of the entity position
        if (clickedOnEntity(entity, window))
        {
            if ((entity->getOpacity() < 255) && (*statemanager->uiState == UI_STATE::MAIN)) // --- do we really need to check the state twice (see updateinput)
            {
                debugger->my_debug_timer("InputManager() function called.");    // timestamps for console
                soundPop2->play();
                entity->setOpacity(255);
                entity->setId(xMarker);                                             // set our player marker
                std::cout << entity->getId() << std::endl;
                *statemanager->gameState = GAME_STATE::AI;                      // gamestate back to AI
            }
        }
    }
}

// Our logic check to see if our mouse position is inside of our game window and entity rect
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
    else
    {
        return false;
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