#include "GameState.h"
#include "Window.h"
#include "WindowParams.h"
#include "DeltaTime.h"
#include "Entity.h"

Game::Game(const char* id, int width, int height, bool fullscreen)
{
	create(id, width, height, fullscreen);
}

Game::Game()
{
	create("NoID", 800, 600, false);
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

	// Let's create our first entity
	background = new Entity("Graphics/Background_Board.png");
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
	//updateInput();
}

void Game::render()
{
	clear();
	draw();
	display();
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
void Game::draw()
{
	// Background
	background->setPosition(400, 300);
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