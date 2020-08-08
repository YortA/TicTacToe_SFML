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

	// Text
	winText = new sf::Text;
	lossText = new sf::Text;
	winPopText = new sf::Text;
	lossPopText = new sf::Text;
	drawPopText = new sf::Text;

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

	quitButton->getRect()->setSize(sf::Vector2f(window->getWidth() / 9, window->getHeight() / 9));
	quitButton->setOrigin(0.0f, 0.0f);
	quitButton->setPosition(playButton->getPosition().x + quitButton->getWidth() + 20, playButton->getPosition().y);

	// Text setup
	ui->createScoreText("USER ", 0, winText);
	winText->setFillColor(sf::Color::Blue);
	winText->setOrigin(0.0f, 0.0f);
	winText->setPosition(restartButton->getPosition().x - 45, restartButton->getPosition().y - 125.f);

	ui->createScoreText("AI ", 0, lossText);
	lossText->setFillColor(sf::Color::Red);
	lossText->setOrigin(0.0f, 0.0f);
	lossText->setPosition(quitButton->getPosition().x - 5, quitButton->getPosition().y - 125.f);

	ui->createMsgText("WIN", winPopText);
	winPopText->setFillColor(sf::Color::Color(0, 0, 255, 0));
	winPopText->setOrigin(0.0f, 0.0f);
	winPopText->setPosition(250, 50);

	ui->createMsgText("LOSS", lossPopText);
	lossPopText->setFillColor(sf::Color::Color(255, 0, 0, 0));
	lossPopText->setOrigin(0.0f, 0.0f);
	lossPopText->setPosition(190, 50);

	ui->createMsgText("DRAW", drawPopText);
	drawPopText->setFillColor(sf::Color::Color(240, 255, 0, 0));
	drawPopText->setOrigin(0.0f, 0.0f);
	drawPopText->setPosition(190, 50);
}

// Reset our gameboard
void Game::reset()
{
	*statemanager->gameState = GAME_STATE::PLAYER;

	std::cout << "Wins: " << wins << std::endl;
	std::cout << "Losses: " << losses << std::endl;

	wins = 0;
	losses = 0;
	boolgameEndSound = true;		// ready our win sound

	// reset entities id & markers to null
	resetOtoX();
}

// Check to make sure our cell is reset before allowing a click
void Game::resetOtoX()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sf::Vector2u textureSize = markerVec[i][j]->getTexture()->getSize();
			textureSize.x /= 2;			// cut our spritesheet in half
			markerVec[i][j]->getRect()->setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));	// set origin to 0,0 of the sprite sheet (top left)
			markerVec[i][j]->setOpacity(0.f);
			markerVec[i][j]->setId('_');
		}
	}

}

void Game::destroy()
{
	// delete our gridmarkers
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete markerVec[i][j];
		}
	}

	// delete ui entities
	delete titleScreen;
	delete playButton;
	delete restartButton;
	delete quitButton;

	// delete sound entities
	delete soundPop1;
	delete musicbg;

	// delete game entities
	delete background;
	delete gridbg;

	// delete text
	delete winText;
	delete winPopText;
	delete lossText;
	delete lossPopText;
	delete drawPopText;

	// delete game engine
	delete ai;
	delete ui;
	delete inputmanager;
	delete statemanager;
	delete deltatime;
	delete window;
}


// Game loop functions
void Game::update()
{
	updateDelta();
	updateEvent();
	updateGameTimer();
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
	if (*statemanager->uiState == UI_STATE::TITLE)					// title screen
	{
		inputmanager->update(playButton, statemanager, window);
	}
	else if (*statemanager->uiState == UI_STATE::MAIN)				// if we're on main
	{
		if (inputmanager->clickedOnEntity(restartButton, window))		// allow restart button click
		{
			*statemanager->uiState = UI_STATE::MAIN;
			reset();
		}
		if (inputmanager->clickedOnEntity(quitButton, window))			// allow quit button click
		{
			*statemanager->uiState = UI_STATE::TITLE;
			reset();
		}
	}

	// Play marker input
	if (inputmanager->DidMouseTrigger() && !GameEnd() && *statemanager->uiState == UI_STATE::MAIN)
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
}

// All AI update functions
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
		if (boolgameEndSound)			// play our game sound on win
		{
			boolgameEndSound = false;
			soundWinner->play();
			boolNewGameTimer = true;	// we set our "new game" timer
		}

		if (!boolNewGameTimer)			// once the timer returns false, we allow the conditions
		{
			if (ai->checkWin_Game(AI::PLAYER::USER, markerVec))		// player wins
			{
				// text for player wins
				*statemanager->gameState = GAME_STATE::AI;
				boolgameEndSound = true;
				resetOtoX();
				++wins;
				winPopText->setFillColor(sf::Color::Color(0, 0, 255, 0));
				winPopText->setOutlineThickness(0);
			}
			else if (ai->checkWin_Game(AI::PLAYER::COMPUTER, markerVec))		// ai wins
			{
				// text for ai wins, tells player they start
				*statemanager->gameState = GAME_STATE::PLAYER;
				boolgameEndSound = true;
				resetOtoX();
				++losses;
				lossPopText->setFillColor(sf::Color::Color(255, 0, 0, 0));
				lossPopText->setOutlineThickness(0);
			}
		}
		
	}
	// check for a draw
	else
	{
		int fullsquares = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check to make sure our cell is empty before allowing a click
				if (markerVec[i][j]->getId() != '_')
				{
					++fullsquares;
				}
			}
		}
		// looks like a draw!
		if (fullsquares == 9)
		{
			// manual timer to fix outside of gameEnd() loop
			endgametimer += .1f;

			drawPopText->setFillColor(sf::Color::Color(240, 255, 0, 255));
			drawPopText->setOutlineThickness(20);
			if (endgametimer >= 7.f)
			{
				boolgameEndSound = true;
				endgametimer = 0.0f;
				drawPopText->setFillColor(sf::Color::Color(240, 255, 0, 0));
				drawPopText->setOutlineThickness(0);
				resetOtoX();
			}
		}
	}
	
	// Update our UI win/loss text
	ui->createScoreText("USER ", wins, winText);
	ui->createScoreText("AI ", losses, lossText);
}

// Game timer for our "Winner/Loser"
bool Game::updateGameTimer()
{
	if (boolNewGameTimer)
	{
		endgametimer += .1f;		// timer is updated with framerate SEE: window->getWindow()->setFramerateLimit(60);
		if (ai->checkWin_Game(AI::PLAYER::USER, markerVec))		// display win text
		{
			winPopText->setFillColor(sf::Color::Color(0, 0, 255, 255));
			winPopText->setOutlineThickness(20);
		}
		else if (ai->checkWin_Game(AI::PLAYER::COMPUTER, markerVec))		// display loss text
		{
			lossPopText->setFillColor(sf::Color::Color(255, 0, 0, 255));
			lossPopText->setOutlineThickness(20);
		}

		if (endgametimer >= 7.f)		// check for timer
		{
			boolNewGameTimer = false;
			endgametimer = 0.0f;
			return true;
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

		// Draw text
		window->draw(*winText);
		window->draw(*lossText);

		// Grid
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				window->draw(*markerVec[i][j]->getRect());
			}
		}

		// UI
		window->draw(*winPopText);
		window->draw(*lossPopText);
		window->draw(*drawPopText);
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