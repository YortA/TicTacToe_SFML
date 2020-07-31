#include "AI.h"
#include "Entity.h"
#include "StateManager.h"

#include "MYDEBUGHELPER.h"

AI::AI()
{

}

AI::~AI()
{

}

// POSSIBLE BUG
// our isEmptySquare function is causing a runtime error? / Crashes?

// Let's check to see if our cell is empty
bool AI::hasEmptySquare(char copyMarkervec[3][3])
{
	// loop through our 2d array and check for empty markers
	for (int i = 0; 0 < 3; i++)
	{
		for (int j = 0; 0 < 3; j++)
		{
			if (copyMarkervec[i][j] == emptyMarker)					// if the id (char) is '_' then the cell is empty.
			{
				return true;
			}
		}
	}
	// If the cell is taken
	return false;
}

// Check to see if the PLAYER or AI won
bool AI::checkWin(PLAYER player, char copyMarkervec[3][3])
{
	// We assign our playerValue to (1 or 2). This will let us know who wins the game
	char playerValue = 0;
	if (player == PLAYER::USER)
		playerValue = humanMarker;
	else if (player == PLAYER::COMPUTER)
		playerValue = aiMarker;

	// Check our rows for three matching
	for (int row = 0; row < 3; row++)
	{
		if (copyMarkervec[row][0] == copyMarkervec[row][1] &&
			copyMarkervec[row][1] == copyMarkervec[row][2])
		{
			if (copyMarkervec[row][0] == playerValue)			// we need to check if the winner is a player or AI.
			{
				return true;
			}
		}
	}

	// Check our columns for three matching
	for (int col = 0; col < 3; col++)
	{
		if (copyMarkervec[0][col] == copyMarkervec[1][col] &&
			copyMarkervec[1][col] == copyMarkervec[2][col])
		{
			if (copyMarkervec[0][col] == playerValue)			// we need to check if the winner is a player or AI.
			{
				return true;
			}
		}
	}

	// Check for diagonals for three matching
	if (copyMarkervec[0][0] == copyMarkervec[1][1] && copyMarkervec[1][1] == copyMarkervec[2][2])
	{
		if (copyMarkervec[0][0] == playerValue)
			return true;
	}

	if (copyMarkervec[0][2] == copyMarkervec[1][1] && copyMarkervec[1][1] == copyMarkervec[2][0])
	{
		if (copyMarkervec[0][2] == playerValue)
		{
			return true;
		}
	}

	// Didn't win
	return false;
}

bool AI::gameOver(char copyMarkervec[3][3])
{
	if (checkWin(PLAYER::USER, copyMarkervec)) { return true; }
	else if (checkWin(PLAYER::COMPUTER, copyMarkervec)) { return true; }
	return !hasEmptySquare(copyMarkervec);		// If no one wins, we return empty cell -- mirror the call for 
}


int AI::score(char copyMarkervec[3][3])
{
	// see AI.h for explanation
	if (checkWin(PLAYER::USER, copyMarkervec))
	{
		//std::cerr << "DEBUG: score() return 10" << std::endl;
		return 1000;
	}
	if (checkWin(PLAYER::COMPUTER, copyMarkervec))
	{
		//std::cerr << "DEBUG: score() return -10" << std::endl;
		return -1000;
	}
	return 0; // draw
}

//
//
//


// ####################### AI TICTACTOE ALGORITHM SECTION #######################

// Our main minimax function
// Giant reursive function
AI::Moves AI::minimax(std::vector<std::vector<Entity*>> markerVec)
{
	char copyMarkervec[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			copyMarkervec[i][j] = markerVec[i][j]->getId();
			std::cout << copyMarkervec[i][j] << std::endl;	// debug to ensure our values are right
		}
	}

	int bestMove = 100000;
	Moves duhbigmove;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (copyMarkervec[i][j] == emptyMarker)
			{
				copyMarkervec[i][j] = aiMarker;
				int tempMax = maxReturn(copyMarkervec, 0);	// recursive function for min/max
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;						// assign our move object x and y value, then reset to empty
					duhbigmove.x = i;
					duhbigmove.y = j;
					debugger->my_debug_timer("DEBUG: minimax() fn called.");	// debug for console timings
				}
				copyMarkervec[i][j] = emptyMarker;			// reset our cell back to empty
			}
		}
	}
	return duhbigmove;										// return our final x, y values for permanent placement in cell
}


int AI::maxReturn(char copyMarkervec[3][3], int iteration)
{
	if (gameOver(copyMarkervec)) return score(copyMarkervec);	// check to see if it's a winning placement and the returned score value

	Moves duhbigmove;
	int bestMove = -100000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (copyMarkervec[i][j] == emptyMarker)				// if our cell is equal to empty
			{
				copyMarkervec[i][j] = humanMarker;	// 
				int tempMin = minReturn(copyMarkervec, iteration + 1);			// recursive function for min/max
				if (tempMin >= bestMove)
				{
					bestMove = tempMin;							// assign our move object x and y value, then reset to empty
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				copyMarkervec[i][j] = emptyMarker;				// reset our cell back to empty
			}
		}
	}
	return bestMove;
}

int AI::minReturn(char copyMarkervec[3][3], int iteration)
{
	if (gameOver(copyMarkervec))
	{
		int metric = score(copyMarkervec);
		return metric - signFN(metric) * iteration;
		//return score(copyMarkervec);
	}

	Moves duhbigmove;
	int bestMove = 100000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (copyMarkervec[i][j] == emptyMarker)
			{
				copyMarkervec[i][j] = aiMarker;
				int tempMax = maxReturn(copyMarkervec, iteration + 1);
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				copyMarkervec[i][j] = emptyMarker;			
			}
		}
	}
	return bestMove;
}

int AI::signFN(int num)
{
	if (num == 0) return 0;
	return num / abs(num);
}

// Allows AI to place a marker
void AI::switchFromXtoO(Entity* entity)
{
	// This gets our "O"
	sf::Vector2u textureSize = entity->getTexture()->getSize();
	textureSize.x /= 2;			// Only two images in sprite sheet -- this gets our "O" instead of "X"

	entity->getRect()->setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 0, textureSize.x, textureSize.y));
	entity->setId('O');
}

//
//
//

// our 2nd checkWin_Game, but this time we pass our referenced board from gamestate.cpp
bool AI::checkWin_Game(PLAYER player, std::vector<std::vector<class Entity*>> markerVec)
{
	// check if user or ai has won, passed by argument
	char playerValue = 0;
	if (player == PLAYER::USER)
		playerValue = humanMarker;
	else if (player == PLAYER::COMPUTER)
		playerValue = aiMarker;

	// Check our rows for three matching
	for (int row = 0; row < 3; row++)
	{
		if (markerVec[row][0]->getId() == markerVec[row][1]->getId() &&
			markerVec[row][1]->getId() == markerVec[row][2]->getId())
		{
			if (markerVec[row][0]->getId() == playerValue)			// we check if the winner is a player or AI in playeValue declaration
			{
				return true;
			}
		}
	}

	// Check our columns for three matching
	for (int col = 0; col < 3; col++)
	{
		if (markerVec[0][col]->getId() == markerVec[1][col]->getId() &&
			markerVec[1][col]->getId() == markerVec[2][col]->getId())
		{
			if (markerVec[0][col]->getId() == playerValue)
			{
				return true;
			}
		}
	}

	// Check for diagonals for three matching
	if (markerVec[0][0]->getId() == markerVec[1][1]->getId() && markerVec[1][1]->getId() == markerVec[2][2]->getId())
	{
		if (markerVec[0][0]->getId() == playerValue)
			return true;
	}

	if (markerVec[0][2]->getId() == markerVec[1][1]->getId() && markerVec[1][1]->getId() == markerVec[2][0]->getId())
	{
		if (markerVec[0][2]->getId() == playerValue)
		{
			return true;
		}
	}

	// Didn't win
	return false;
}