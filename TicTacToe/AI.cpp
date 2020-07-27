#include "AI.h"

// Let's check to see if our cell is empty
bool AI::isEmptySquare(int board[3][3])
{
	for (int i = 0; 0 < 3; i++)
	{
		for (int j = 0; 0 < 3; j++)
		{
			// If the marker == -1, the cell is empty. return true
			if (board[i][j] == -1)
			{
				return true;
			}
		}
	}
	// If the cell is taken, return false.
	return false;
}


// Check to see if the PLAYER or AI won
bool AI::checkWin(PLAYER player, int board[3][3])
{
	// We assign our playerValue to (1 or 2). This will let us know who wins the game
	int playerValue = 0;
	if (player == PLAYER::HUMAN)
		playerValue = 1;
	else if (player == PLAYER::AI)
		playerValue = 2;

	// Check our rows for three matching
	for (int row = 0; row < 3; row++)
	{
		if (board[row][0] == board[row][1] &&
			board[row][1] == board[row][2])
		{
			if (board[row][0] == playerValue)			// we need to check if the winner is a player or AI.
			{
				return true;
			}
		}
	}

	// Check our columns for three matching
	for (int col = 0; col < 3; col++)
	{
		if (board[0][col] == board[1][col] &&
			board[1][col] == board[2][col])
		{
			if (board[0][col] == playerValue)			// we need to check if the winner is a player or AI.
			{
				return true;
			}
		}
	}

	// Check for diagonals for three matching
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		if (board[0][0] == playerValue)
			return true;
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
	{
		if (board[0][2] == playerValue)
		{
			return true;
		}
	}

	// Didn't win
	return false;
}

bool AI::gameOver(int board[3][3])
{
	// how can we actually check if we win by passing PLAYER or AI without the board?
	if (checkWin(PLAYER::HUMAN))
	{
		return true;
	}
	else if (checkWin(PLAYER::AI))
	{
		return true;
	}
}


//
//
//


// ####################### AI TICTACTOE ALGORITHM SECTION #######################

// Our main minimax function

// Giant reursive function
int AI::minimax(int board[3][3])
{
	int bestMove = 1000;
	AI duhbigmove;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == -1)			// if our cell is equal to empty
			{
				board[i][j] = aiMarker;		// 
				int tempMax = maxReturn(board);
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				board[i][j] = -1;			// reset our cell back to empty
			}
		}
	}
	return bestMove;
}


int AI::maxReturn(int board[3][3])
{
	AI duhbigmove;
	int bestMove = -1000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == -1)			// if our cell is equal to empty
			{
				board[i][j] = humanMarker;	// 
				int tempMin = minReturn(board);			// recursive function for min/max
				if (tempMin >= bestMove)
				{
					bestMove = tempMin;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				board[i][j] = -1;			// reset our cell back to empty
			}
		}
	}
	return bestMove;
}

int AI::minReturn(int board[3][3])
{
	AI duhbigmove;
	int bestMove = 1000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == -1)			// if our cell is equal to empty
			{
				board[i][j] = aiMarker;		// 
				int tempMax = maxReturn(board);			// recursive function for min/max
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				board[i][j] = -1;			// reset our cell back to empty
			}
		}
	}
	return bestMove;
}
