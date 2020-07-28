#include "GameState.h"
#include "Window.h"
#include "WindowParams.h"
#include "DeltaTime.h"
#include "Entity.h"
#include "StateManager.h"
#include "InputManager.h"
#include "AI.h"


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

// Main game engine create
void Game::create(const char* id, int width, int height, bool fullscreen)
{
	window = new Window{ id, width, height, fullscreen };
	deltatime = new DeltaTime;
	statemanager = new StateManager(State::GAME_STATE::PLAYER);				// we could use our default, but for now we'll be implicit
	inputmanager = new InputManager;
	ai = new AI;

	createEntities();
}

void Game::createEntities()
{
	// Game Entitys
	background = new Entity("Graphics/Background_Board.png");
	gridbg = new Entity("Graphics/Grid.png");

	// MAKE ENTITY CONSTRUCTOR FOR GRIDBG LATER HAHA
	gridbg->setOrigin(0.f, 0.f);
	gridbg->setPosition(200, 25);

	// Game functionality
	// Clear our board for marker inputs (x's and o's)
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			boardArray[i][j] = NO_MARKER;
		}
	}

	// Create our marker entities for placement
	for (int i = 0; i < 3; i++)
	{
		std::vector<Entity*> entityRow;
		markerVec.push_back(entityRow);

		for (int j = 0; j < 3; j++)
		{	
			// 2 == SPRITErow; 1 == SPRITEcolumn
			Entity* entity = new Entity("Graphics/XandO.png", gridbg->getRect()->getSize().x / 3, gridbg->getRect()->getSize().y / 3, 2, 1);
			entity->setId('_');																	// sets the grid to empty '_'
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
	draw();
	display();
}

// Allows us to call our update functionality for mouse clicks on screen
void Game::updateInput()
{
	//inputmanager->update(background, statemanager, window);			// what is this even for

	// Iterate through all of the cells
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inputmanager->update(markerVec[i][j], statemanager, window);
		}
	}
}

void Game::updateAI()
{
	ai->moves = ai->minimax(markerVec);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((ai->moves.x == markerVec[i][j]->getGridPosition()->x) &&
				(ai->moves.y == markerVec[i][j]->getGridPosition()->y))
			{
				ai->switchFromXtoO(markerVec[i][j]);
				markerVec[i][j]->setOpacity(255);
				markerVec[i][j]->setId('O');
			}
		}
	}
}

// notes
// we can invoke the check if empty function in ai->checkifempty and pass our arrayBoard[][]?





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