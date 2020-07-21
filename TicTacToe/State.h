// We use this state.h/.cpp to control and reference in both game and statemanager
// We can add more states later, for example -- menu, pause, etc.
#pragma once

class State
{
private:
public:
	State();
	~State();

	// State enums
	enum class GAME_STATE
	{
		PLAYER,			// player == 0
		AI,
		GAMEOVER
	};

	// Initialize our STATES
	GAME_STATE gameState;
};