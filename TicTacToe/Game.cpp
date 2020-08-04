#include "Game.h"
#include "Window.h"
#include "WindowParams.h"
#include "DeltaTime.h"
#include "Entity.h"
#include "StateManager.h"
#include "InputManager.h"
#include "AI.h"
#include "Sound.h"
#include "UI.h"

// SFML INCLUDES
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Keyboard.hpp"

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
	statemanager = new StateManager;				// we could use our default, but for now we'll be implicit
	inputmanager = new InputManager;									// user functions
	ai = new AI;
	ui = new UI;

	// Game Entities
	background = new Entity("Graphics/Background_Board.png");
	gridbg = new Entity("Graphics/Grid.png");

	// Sound Entities
	soundPop1 = new Sound("Sounds/pop_1.wav");
	soundWinner = new Sound("Sounds/winner_pop_1.wav");
	musicbg = new Sound("Sounds/game_music.wav", 25.f);

	// UI Entities
	titleScreen = new Entity("Graphics/title_screen.png", window->getWidth(), window->getHeight(), 1, 1);

	playButton = ui->createPlayButton();
	restartButton = ui->createRestartButton();
	quitButton = ui->createQuitButton();

	window->getWindow()->setFramerateLimit(60);
	createMarkerGrid();													// initialize all of our game objects
	setup();
}

void Game::setup()
{
	// State setup
	*statemanager->gameState = GAME_STATE::PLAYER;
	*statemanager->uiState = UI_STATE::TITLE;

	// Background setup
	background->setOrigin(0.0f, 0.0f);

	// Sound Entitys
	musicbg->playMusic();

	// UI setup
	titleScreen->setOrigin(0.f, 0.f);

	playButton->getRect()->setSize(sf::Vector2f(window->getWidth() / 9, window->getHeight() / 9));
	playButton->setOrigin(0.0f, 0.0f);
	playButton->setPosition((window->getWidth() / 2) - playButton->getWidth() / 2, window->getHeight() - playButton->getHeight() - 20);

	restartButton->getRect()->setSize(sf::Vector2f(window->getWidth() / 9, window->getHeight() / 9));
	restartButton->setOrigin(0.0f, 0.0f);
	restartButton->setPosition(playButton->getPosition().x - restartButton->getWidth() - 20, playButton->getPosition().y);
	restartButton->setId('R');

	quitButton->getRect()->setSize(sf::Vector2f(window->getWidth() / 9, window->getHeight() / 9));
	quitButton->setOrigin(0.0f, 0.0f);
	quitButton->setPosition(playButton->getPosition().x + quitButton->getWidth() + 20, playButton->getPosition().y);
	quitButton->setId('Q');
}

void Game::destroy()
{
	// delete game engine
	delete window;
	delete deltatime;
	delete statemanager;
	delete inputmanager;
	delete ai;
	delete ui;

	// delete game entities
	delete background;
	delete gridbg;

	// delete sound entities
	delete soundPop1;
	delete musicbg;

	// delete ui entities
	delete titleScreen;
	delete playButton;
	delete restartButton;
	delete quitButton;

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
	updateWinner();
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


	if (*statemanager->uiState == UI_STATE::TITLE)
	{
		inputmanager->update(playButton, statemanager, window);
		inputmanager->update(restartButton, statemanager, window);
		inputmanager->update(quitButton, statemanager, window);
	}

	else if (inputmanager->DidMouseTrigger() && !GameEnd() && *statemanager->uiState == UI_STATE::MAIN)
	{
		// Iterate through all of the cells
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check to make sure our cell is empty before allowing a click
				if (markerVec[i][j]->getId() == '_')
				{
					inputmanager->update(markerVec[i][j], statemanager, window);
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
	{
		*statemanager->uiState = UI_STATE::MAIN;
	}

}

void Game::updateAI()
{
	if (*statemanager->gameState == GAME_STATE::AI && !GameEnd())
	{
		// update based on frame (ghetto timer)
		turntimer += .1f;
		if (turntimer >= 5.f)
		{
			AI::Moves moves = ai->minimax(markerVec);			// get our minimax x and y
			Entity* targetcell = markerVec[moves.x][moves.y];	// save our location
			ai->switchFromXtoO(targetcell);						// call our placement marker
			debugger->my_debug_timer2();						// debug time stamp
			std::cerr << "DEBUG: Best move is: [" << moves.x << "][" << moves.y << "]" << std::endl;		// debug time stamp
			targetcell->setOpacity(255);						// switch the opacity
			soundPop1->play();									// play our 'O' sound
			*statemanager->gameState = GAME_STATE::PLAYER;		// change the state, now it's the player's turn
			turntimer = 0.0f;									// reset timer after AI move
		}
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
	{
		return false;
	}
}

// makes winner sound based on if bool gameend returns true
void Game::updateWinner()
{
	if (GameEnd())
	{
		if (boolgameEndSound)
		{
			boolgameEndSound = false;
			soundWinner->play();
		}
	}
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
	// Draw our game.
	if (*statemanager->uiState == UI_STATE::TITLE)
	{
		window->draw(*titleScreen->getRect());
		window->draw(*playButton->getRect());
	}
	else if (*statemanager->uiState == UI_STATE::MAIN)
	{
		// Background
		window->draw(*background->getRect());
		window->draw(*gridbg->getRect());

		// UI
		window->draw(*restartButton->getRect());
		window->draw(*quitButton->getRect());

		// Grid
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				window->draw(*markerVec[i][j]->getRect());
			}
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

// Creates our marker grid for placement
void Game::createMarkerGrid()
{
	// Set our game entity variables
	gridbg->getRect()->setSize(sf::Vector2f(300.f, 300.f));
	gridbg->setOrigin(0.f, 0.f);
	gridbg->setPosition(250, 25);

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
			markerVec[i][j]->setOpacity(0);                                                        // let's just test our opacity on the "empty markers"
			// Set our marker position based off of our grid rect origin
			markerVec[i][j]->setPosition(
			(((gridbg->getRect()->getSize().x) / 3) * j) + gridbg->getPosition().x,                // we get the gridbg position for the starting positions
				(((gridbg->getRect()->getSize().y) / 3) * i) + gridbg->getPosition().y);        // and then add them. so; x = 0 + 250, 100 + 250 = 350, etc.
		}
	}
}