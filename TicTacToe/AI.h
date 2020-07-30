#pragma once
#include <vector>

class AI
{
private:
	char humanMarker = 'X';
	char aiMarker = 'O';
	char emptyMarker = '_';

public:
	AI();
	~AI();
	
	struct Moves
	{
		int x = 0;		// our rows
		int y = 0;		// our cols
	};

	/*enum class Stuff
	{
		PLAYER,
		AI
	};*/

	Moves moves;

	void switchFromXtoO(class Entity* entity);

	bool isEmptySquare(std::vector<std::vector<class Entity*>> markerVec);
	bool checkWin(class StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);
	bool gameOver(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);

	Moves minimax(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);
	int maxReturn(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);
	int minReturn(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);
	int score(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);


};