#include "AI.h"
#include "Entity.h"
#include "StateManager.h"

#include <iostream>				// debug purposes

AI::AI()
{

}

AI::~AI()
{

}

// BUG
// our isEmptySquare function is causing a runtime error?

// Let's check to see if our cell is empty
bool AI::isEmptySquare(char copyMarkervec[3][3])
{
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
	// BUG
	// how can we actually check if we win by passing PLAYER or AI without the markerVec?
	if (checkWin(PLAYER::USER, copyMarkervec)) { return true; }
	else if (checkWin(PLAYER::COMPUTER, copyMarkervec)) { return true; }
	return isEmptySquare(copyMarkervec);
}


int AI::score(char copyMarkervec[3][3])
{
	if (checkWin(PLAYER::USER, copyMarkervec))
	{
		//std::cerr << "DEBUG: score() return 10" << std::endl;
		return 10;
	}
	if (checkWin(PLAYER::COMPUTER, copyMarkervec))
	{
		//std::cerr << "DEBUG: score() return -10" << std::endl;
		return -10;
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
			std::cout << copyMarkervec[i][j] << std::endl;		// debug to ensure our values are right
		}
	}

	int bestMove = 100;
	Moves duhbigmove;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (copyMarkervec[i][j] = emptyMarker)		// if our cell is equal to empty
			{
				copyMarkervec[i][j] = aiMarker;					// 
				int tempMax = maxReturn(copyMarkervec);
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
					std::cerr << "DEBUG: minimax() fn called." << std::endl;
				}
				copyMarkervec[i][j] = emptyMarker;			// reset our cell back to empty
			}
		}
	}
	return duhbigmove;
}


int AI::maxReturn(char copyMarkervec[3][3])
{
	if (gameOver(copyMarkervec)) return score(copyMarkervec);

	Moves duhbigmove;
	int bestMove = -1000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (copyMarkervec[i][j] == emptyMarker)					// if our cell is equal to empty
			{
				copyMarkervec[i][j] = humanMarker;	// 
				int tempMin = minReturn(copyMarkervec);			// recursive function for min/max
				if (tempMin >= bestMove)
				{
					bestMove = tempMin;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				copyMarkervec[i][j] = emptyMarker;						// reset our cell back to empty
			}
		}
	}
	return bestMove;
}

int AI::minReturn(char copyMarkervec[3][3])
{
	if (gameOver(copyMarkervec)) return score(copyMarkervec);

	Moves duhbigmove;
	int bestMove = 1000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (copyMarkervec[i][j] == emptyMarker)					// if our cell is equal to empty
			{
				copyMarkervec[i][j] = aiMarker;		// 
				int tempMax = maxReturn(copyMarkervec);			// recursive function for min/max
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				copyMarkervec[i][j] = emptyMarker;						// reset our cell back to empty
			}
		}
	}
	return bestMove;
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