#pragma once

class InputManager
{
private:
	class myDebugger* debugger = nullptr;
	bool mouseState = false;

public:
	InputManager();
	~InputManager();
	bool DidMouseTrigger();
	void update(class Entity* entity, class StateManager* statemanager, class Window* window);
};