#pragma once

// Our main game class that controls all functionality

class Game
{
private:
	// Pointer classes to render our window
	class Window* window = nullptr;
	class DeltaTime* deltatime = nullptr;

	class Entity* background = nullptr;

	// Rendering functions
	void clear();
	void draw();
	void display();

	// Rendering "heartbeat" updates
	void updateDelta();
	void updateEvent();
	//void updateInput();

	// Add other functions later

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