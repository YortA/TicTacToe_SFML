#include "GameState.h"
#include "Window.h"
#include "WindowParams.h"
#include "DeltaTime.h"
#include "Entity.h"
#include "StateManager.h"
#include "InputManager.h"
#include "AI.h"
#include "Sound.h"
#include "SFML/Window/Mouse.hpp"

// C++ / Windows includes
#include <iostream>

#include "MYDEBUGHELPER.h"

Game::Game(const char* id, int width, int height, bool fullscreen)
{
	create(id, width, height, fullscreen);
}

Game::Game()
{
	create("NoID", 800, 600, false);		// something went wrong with our constructor (check MAIN.CPP)
}

Game::~Game()
{
	destroy();
}

//
//
//

// Main game engine create
void Game::create(const char* id, int width, int height, bool fullscreen)
{
	window = new Window{ id, width, height, fullscreen };				// create a new window object and pass our params
	deltatime = new DeltaTime;											// create a time object (to be used later)
	statemanager = new StateManager(GAME_STATE::PLAYER);				// we could use our default, but for now we'll be implicit
	inputmanager = new InputManager;									// user functions
	ai = new AI;														// ai functions

	createEntities();													// initialize all of our game objects
}

void Game::createEntities()
{
	// Game Entitys
	background = new Entity("Graphics/Background_Board.png");
	gridbg = new Entity("Graphics/Grid.png");

	// set our game entity variables
	gridbg->getRect()->setSize(sf::Vector2f(300.f, 300.f));
	gridbg->setOrigin(0.f, 0.f);
	gridbg->setPosition(250, 25);

	// Sound Entitys
	soundPop1 = new Sound("Sounds/pop_1.wav");
	//soundPop2 = new Sound("Sounds/pop_2.wav");

	// create our marker entities for placement x and o placements
	for (int i = 0; i < 3; i++)
	{
		std::vector<Entity*> entityRow;
		markerVec.push_back(entityRow);

		for (int j = 0; j < 3; j++)
		{	
			// 2 == SPRITErow; 1 == SPRITEcolumn
			Entity* entity = new Entity("Graphics/XandO.png", gridbg->getRect()->getSize().x / 3, gridbg->getRect()->getSize().y / 3, 2, 1);
			entity->setGridPosition(i, j);														// sets a [i][j] position relative to the grid (e.g. [0][0] - [2][2])
			markerVec[i].push_back(entity);

			markerVec[i][j]->setOrigin(0.f, 0.f);
			markerVec[i][j]->setOpacity(0);														// let's just test our opacity on the "empty markers"
			// Set our marker position based off of our grid rect origin
			markerVec[i][j]->setPosition(
			(((gridbg->getRect()->getSize().x) / 3) * j) + gridbg->getPosition().x,				// we get the gridbg position for the starting positions
				(((gridbg->getRect()->getSize().y) / 3) * i) + gridbg->getPosition().y);		// and then add them. so; x = 0 + 250, 100 + 250 = 350, etc.
		}
	}
}

void Game::destroy()
{
	// delete game engine
	delete window;
	delete deltatime;
	delete statemanager;
	delete inputmanager;
	delete ai;

	// delete game entities
	delete background;
	delete gridbg;

	// delete sound entities
	delete soundPop1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete markerVec[i][j];
		}
	}
}


// Game loop functions
void Game::update()
{
	updateDelta();
	updateEvent();
	updateInput();		// player input
	updateAI();			// ai input
}

void Game::render()
{
	clear();
	draw();				// draw things in our window
	display();
}

// Allows us to call our update functionality for mouse clicks on screen
void Game::updateInput()
{
	if (inputmanager->DidMouseTrigger() && !GameEnd())
	{
		// Iterate through all of the cells
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				inputmanager->update(markerVec[i][j], statemanager, window);
			}
		}
	}
}

void Game::updateAI()
{
	if (*statemanager->gameState == GAME_STATE::AI && !GameEnd())
	{
		AI::Moves moves = ai->minimax(markerVec);			// get our minimax x and y
		Entity* targetcell = markerVec[moves.x][moves.y];	// save our location
		ai->switchFromXtoO(targetcell);						// call our placement marker
		debugger->my_debug_timer2();						// debug time stamp
		std::cerr << "DEBUG: Best move is: [" << moves.x << "]["<< moves.y << "]" << std::endl;		// debug time stamp
		targetcell->setOpacity(255);						// switch the opacity
		soundPop1->play();
		*statemanager->gameState = GAME_STATE::PLAYER;		// change the state, now it's the player's turn
	}
}

// logical check to see if our USER or AI has won
bool Game::GameEnd()
{
	if (ai->checkWin_Game(AI::PLAYER::COMPUTER, markerVec) || ai->checkWin_Game(AI::PLAYER::USER, markerVec))
	{
		return true;
	}
	else
		return false;
}

// Update our deltatime -- we will (maybe) use this to track time in-game
void Game::updateDelta()
{
	deltatime->update();
}

void Game::updateEvent()
{
	window->handleEvent();
}

// Render functions
void Game::clear()
{
	window->clear();	// call our window clear
}

// Render our entities on-screen
// First drawn object is on the bottom. so, BG>ENTITY1>ENTITY2 -- BG will be below entity1, etc.
void Game::draw()
{
	// Background
	background->setPosition(400, 300);
	window->draw(*background->getRect());
	window->draw(*gridbg->getRect());



	// Grid
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			window->draw(*markerVec[i][j]->getRect());
		}
	}

}

// Display our window
void Game::display()
{
	window->display();
}

// Check to see if our game is still running
bool Game::isRunning()
{
	return window->isOpen();
}