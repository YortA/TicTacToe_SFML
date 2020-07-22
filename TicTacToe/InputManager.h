#pragma once

//#include "SFML/Graphics.hpp"		// need this for mouse functionality

class InputManager
{
private:
	//class StateManager* statemanager;			// probably remove this

public:
	InputManager();
	~InputManager();

	void update(class Entity* entity, class StateManager* statemanager, class Window* window);
};