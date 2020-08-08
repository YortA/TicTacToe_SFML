#pragma once
#include <vector>
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

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
	class UI* ui = nullptr;

	// Initialize entities
	class Entity* background = nullptr;
	class Entity* gridbg = nullptr;

	// Sound entities
	class Sound* soundPop1 = nullptr;
	class Sound* soundWinner = nullptr;
	class Sound* musicbg = nullptr;

	// UI
	// Screens
	class Entity* titleScreen = nullptr;

	// Buttons
	class Entity* playButton = nullptr;
	class Entity* restartButton = nullptr;
	class Entity* quitButton = nullptr;

	// Text
	sf::Text* winText = nullptr;
	sf::Text* winPopText = nullptr;
	sf::Text* lossText = nullptr;
	sf::Text* lossPopText = nullptr;

	sf::Text* drawPopText = nullptr;

	// Rendering functions
	void clear();
	void draw();
	void display();

	// Rendering "heartbeat" updates
	void updateDelta();
	void updateEvent();
	void updateInput();			// player game loop
	void updateAI();			// ai game loop
	void updateWinner();
	bool updateGameTimer();

	// Game Functionality
	std::vector<std::vector<Entity*>> markerVec;	// MD vector hurrr
	bool GameEnd();
	bool boolgameEndSound = true;					// play our "winner" sound
	bool boolNewGameTimer = false;

	// Gets our turn timer
	float turntimer = 0;
	float endgametimer = 0;
	int wins = 0;
	int losses = 0;


public:
	// Constructor/Destructors
	Game();
	Game(const char* id, int width, int height, bool fullscreen);
	~Game();

	void create(const char* id, int width, int height, bool fullscreen);
	void reset();
	void resetOtoX();
	void setup();
	void destroy();

	// Call our update and render members
	void update();
	void render();
	bool isRunning();

	// Entity creator function
	void createMarkerGrid();
};