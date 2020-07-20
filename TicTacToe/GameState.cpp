#include "GameState.h"
#include "Window.h"
#include "WindowParams.h"
#include "DeltaTime.h"

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
}

void Game::destroy()
{
	delete window;
	delete deltatime;
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

// TO BE COMPLETED (RENDER OBJECTS LATER)
void Game::draw()
{
	// banana
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