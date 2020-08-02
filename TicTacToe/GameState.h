#pragma once
#include <vector>
// Our main game class that controls all functionality

class Game
{
private:
	class myDebugger* debugger = nullptr;

	// Pointer classes to render our window
	class Window* window = nullptr;
	class DeltaTime* deltatime = nullptr;
	class StateManager* statemanager = nullptr;
	class InputManager* inputmanager = nullptr;
	class AI* ai = nullptr;

	// Initialize entities
	class Entity* background = nullptr;
	class Entity* gridbg = nullptr;

	// Sound entities
	class Sound* soundPop1 = nullptr;

	// Rendering functions
	void clear();
	void draw();
	void display();

	// Rendering "heartbeat" updates
	void updateDelta();
	void updateEvent();
	void updateInput();			// player game loop
	void updateAI();			// ai game loop


	// Game Functionality
	std::vector<std::vector<Entity*>> markerVec;	// MD vector hurrr
	//int turns = 0;
	bool GameEnd();

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

	// Entity creator function
	void createEntities();
};