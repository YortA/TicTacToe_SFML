#pragma once
#include <vector>

class AI
{
private:
	char humanMarker = 'X';
	char aiMarker = 'O';
	char emptyMarker = '_';

	class myDebugger* debugger = nullptr;

public:
	AI();
	~AI();

	struct Moves
	{
		int x = 0;		// our rows
		int y = 0;		// our cols
	};

	enum class PLAYER
	{
		USER,
		COMPUTER
	};

	//Moves moves;

	void switchFromXtoO(class Entity* entity);

	bool hasEmptySquare(char copyMarkervec[3][3]);
	bool checkWin(PLAYER player, char copyMarkervec[3][3]);
	bool checkWin_Game(PLAYER player, std::vector<std::vector<class Entity*>> markerVec);
	bool gameOver(char copyMarkervec[3][3]);

	Moves minimax(std::vector<std::vector<class Entity*>> markerVec);
	int maxReturn(char copyMarkervec[3][3]);
	int minReturn(char copyMarkervec[3][3]);
	int score(char copyMarkervec[3][3]);


};