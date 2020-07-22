#pragma once
#include <vector>
// Our main game class that controls all functionality

class Game
{
private:
	// Pointer classes to render our window
	class Window* window = nullptr;
	class DeltaTime* deltatime = nullptr;
	class StateManager* statemanager = nullptr;
	class InputManager* inputmanager = nullptr;
	class State* state = nullptr;

	// Initialize entities
	class Entity* background = nullptr;
	class Entity* gridbg = nullptr;
	// Rendering functions
	void clear();
	void draw();
	void display();

	// Rendering "heartbeat" updates
	void updateDelta();
	void updateEvent();
	void updateInput();

	// Game Functionality
	int boardArray[3][3];							// MD array for our board spots
	std::vector<std::vector<Entity*>> markerVec;	// MD vector hurrr

	//class Entity* markerArray[3][3];				// Not in-use

	//int playerTurn;
	//int currentState;

public:
	// Constructor/Destructors
	Game();
	Game(const char* id, int width, int height, bool fullscreen);
	~Game();

	void create(const char* id, int width, int height, bool fullscreen);
	void destroy();

	// Call our update and render members
	void update();
	void render();
	bool isRunning();

	// Add other functions later
};