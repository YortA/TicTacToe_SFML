#pragma once

class InputManager
{
private:
	class myDebugger* debugger = nullptr;
	bool mouseState = false;

public:
	InputManager();
	~InputManager();
	// returns if our mouse is triggered
	bool DidMouseTrigger();
	// user input functionality
	void update(class Entity* entity, class StateManager* statemanager, class Window* window);
};