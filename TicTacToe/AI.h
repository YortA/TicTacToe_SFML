#pragma once
#include <vector>

class AI
{
private:
	char humanMarker = 'X';
	char aiMarker = 'O';
	char emptyMarker = '_';
	//int playerTurn;

public:
	AI();
	~AI();

	//enum class PLAYER { HUMAN, AI };				// We use this enum to figure out whose turn it is
	struct Moves
	{
		int x;		// our rows
		int y;		// our cols
	};

	Moves moves;

	void switchFromXtoO(class Entity* entity);

	bool isEmptySquare(std::vector<std::vector<class Entity*>> markerVec);
	bool checkWin(class StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec);
	bool gameOver(std::vector<std::vector<class Entity*>> markerVec);


	Moves minimax(std::vector<std::vector<class Entity*>> markerVec);
	int maxReturn(std::vector<std::vector<class Entity*>> markerVec);
	int minReturn(std::vector<std::vector<class Entity*>> markerVec);

};