#pragma once

class AI
{
private:
	int x;
	int y;

	int humanMarker = 1;
	int aiMarker = 2;

public:

	enum class PLAYER { HUMAN, AI };				// We use this enum to figure out whose turn it is

	bool isEmptySquare(int board[3][3]);
	bool checkWin(PLAYER player, int board[3][3]);
	bool gameOver(int board[3][3]);


	int minimax(int board[3][3]);
	int maxReturn(int board[3][3]);
	int minReturn(int board[3][3]);

};