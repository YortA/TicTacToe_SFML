#include "GameState.h"
#include "Window.h"
#include "WindowParams.h"
#include "DeltaTime.h"
#include "Entity.h"
#include "StateManager.h"
#include "InputManager.h"


#define NO_MARKER -1		// our empty piece int


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

void Game::create(const char* id, int width, int height, bool fullscreen)
{
	window = new Window(id, width, height, fullscreen);
	deltatime = new DeltaTime;
	statemanager = new StateManager(State::GAME_STATE::PLAYER);				// we could use our default, but for now we'll be implicit
	inputmanager = new InputManager;
	state = new State;

	// Let's create our first entity
	background = new Entity("Graphics/Background_Board.png");

	// Game functionality

	// Clear our board for marker inputs (x's and o's)
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			boardArray[i][j] = NO_MARKER;
		}
	}
}

void Game::destroy()
{
	delete window;
	delete deltatime;
	delete background;
}


// Game loop functions
void Game::update()
{
	updateDelta();
	updateEvent();
	updateInput();
}

void Game::render()
{
	clear();
	draw();
	display();
}

void Game::updateInput()
{
	inputmanager->update(background, state);			// statemanager->state->gameState
}

// Update functions
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
	//background->setOpacity(5); testiing our alpha channel
	window->draw(*background->getRect());
}

void Game::display()
{
	window->display();
}

// Check to see if our game is still running
bool Game::isRunning()
{
	return window->isOpen();
}