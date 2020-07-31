#pragma once
#include <vector>

class AI
{
private:
	// Game markers (no magic values allowed!)
	char humanMarker = 'X';
	char aiMarker = 'O';
	char emptyMarker = '_';

	class myDebugger* debugger = nullptr;

public:
	AI();
	~AI();

	// required for tracking our moves in our minimax algorithm
	struct Moves
	{
		int x = 0;		// our rows
		int y = 0;		// our cols
	};

	// Use this enum to check user and ai status (used with checkwin)
	enum class PLAYER
	{
		USER,
		COMPUTER
	};

	// Allows our AI to place a circle
	void switchFromXtoO(class Entity* entity);

	// ### MINIMAX ALGORITHM SECTION ###
	// searches for an empty square
	bool hasEmptySquare(char copyMarkervec[3][3]);
	// checks for win condition (user and computer)
	bool checkWin(PLAYER player, char copyMarkervec[3][3]);
	bool checkWin_Game(PLAYER player, std::vector<std::vector<class Entity*>> markerVec);
	// returns win + score
	bool gameOver(char copyMarkervec[3][3]);

	// main algorithm -- see below for theory
	Moves minimax(std::vector<std::vector<class Entity*>> markerVec);
	int maxReturn(char copyMarkervec[3][3], int iteration);
	int minReturn(char copyMarkervec[3][3], int iteration);
	// returns score for evaluation function
	int score(char copyMarkervec[3][3]);

	// extracts our sign from a number
	int signFN(int num);

};

// MINIMAX ALGORITHM THEORY
/*

banana

*/
