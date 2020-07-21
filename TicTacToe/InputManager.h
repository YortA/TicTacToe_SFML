#pragma once

#include "SFML/Graphics.hpp"		// need this for mouse functionality
#include "State.h"
#include "Entity.h"

class InputManager
{
private:
	// nothing here
	class Entity* entity;
	class State* state;
	//class StateManager* statemanager;			// probably remove this

public:
	InputManager();
	~InputManager();

	void update(Entity* entity, State* state);
};