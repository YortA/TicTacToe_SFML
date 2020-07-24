#pragma once

class InputManager
{
private:

public:
	InputManager();
	~InputManager();

	void update(class Entity* entity, class StateManager* statemanager, class Window* window);
};