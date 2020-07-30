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
bool AI::isEmptySquare(std::vector<std::vector<Entity*>> markerVec)
{
	for (int i = 0; 0 < 3; i++)
	{
		for (int j = 0; 0 < 3; j++)
		{
			// If the marker == -1, the cell is empty. return true
			if (markerVec[i][j]->getId() == emptyMarker)					// if the id (char) is '_' then the cell is empty.
			{
				return true;
			}
		}
	}
	// If the cell is taken, return false.
	return false;
}




// Check to see if the PLAYER or AI won
bool AI::checkWin(StateManager* statemanager, std::vector<std::vector<Entity*>> markerVec)
{
	// We assign our playerValue to (1 or 2). This will let us know who wins the game
	char playerValue = 0;
	if (*statemanager->gameState == GAME_STATE::PLAYER)
		playerValue = 'X';
	else if (*statemanager->gameState == GAME_STATE::AI)
		playerValue = 'O';

	// Check our rows for three matching
	for (int row = 0; row < 3; row++)
	{
		if (markerVec[row][0] == markerVec[row][1] &&
			markerVec[row][1] == markerVec[row][2])
		{
			if (markerVec[row][0]->getId() == playerValue)			// we need to check if the winner is a player or AI.
			{
				return true;
			}
		}
	}

	// Check our columns for three matching
	for (int col = 0; col < 3; col++)
	{
		if (markerVec[0][col] == markerVec[1][col] &&
			markerVec[1][col] == markerVec[2][col])
		{
			if (markerVec[0][col]->getId() == playerValue)			// we need to check if the winner is a player or AI.
			{
				return true;
			}
		}
	}

	// Check for diagonals for three matching
	if (markerVec[0][0] == markerVec[1][1] && markerVec[1][1] == markerVec[2][2])
	{
		if (markerVec[0][0]->getId() == playerValue)
			return true;
	}

	if (markerVec[0][2] == markerVec[1][1] && markerVec[1][1] == markerVec[2][0])
	{
		if (markerVec[0][2]->getId() == playerValue)
		{
			return true;
		}
	}

	// Didn't win
	return false;
}

bool AI::gameOver(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec)
{
	// BUG
	// how can we actually check if we win by passing PLAYER or AI without the markerVec?
	if (checkWin(statemanager, markerVec))
	{
		return true;
	}
	return isEmptySquare(markerVec);
}


int AI::score(StateManager* statemanager, std::vector<std::vector<class Entity*>> markerVec)
{
	if (*statemanager->gameState == GAME_STATE::PLAYER)
	{
		if (checkWin(statemanager, markerVec)) { return 10; }				// BUG
		std::cerr << "DEBUG: score() return 10" << std::endl;				// our +10 isn't being called for some reason?
	}
	else if (*statemanager->gameState == GAME_STATE::AI)
	{
		if (checkWin(statemanager, markerVec)) { return -10; }
		std::cerr << "DEBUG: score() return -10" << std::endl;
	}
	return 0; // draw
}

//
//
//


// ####################### AI TICTACTOE ALGORITHM SECTION #######################

// Our main minimax function

// Giant reursive function
AI::Moves AI::minimax(StateManager* statemanager, std::vector<std::vector<Entity*>> markerVec)
{
	int bestMove = 100;
	Moves duhbigmove;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (markerVec[i][j]->getId() == emptyMarker)			// if our cell is equal to empty
			{
				markerVec[i][j]->setId(aiMarker);					// 
				int tempMax = maxReturn(statemanager, markerVec);
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
					std::cerr << "DEBUG: minimax() fn called." << std::endl;
				}
				markerVec[i][j]->setId(emptyMarker);			// reset our cell back to empty
			}
		}
	}
	return duhbigmove;
}


int AI::maxReturn(StateManager* statemanager, std::vector<std::vector<Entity*>> markerVec)
{
	if (gameOver(statemanager, markerVec)) return score(statemanager, markerVec);

	Moves duhbigmove;
	int bestMove = -1000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (markerVec[i][j]->getId() == emptyMarker)					// if our cell is equal to empty
			{
				markerVec[i][j]->setId(humanMarker);	// 
				int tempMin = minReturn(statemanager, markerVec);			// recursive function for min/max
				if (tempMin >= bestMove)
				{
					bestMove = tempMin;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				markerVec[i][j]->setId(emptyMarker);						// reset our cell back to empty
			}
		}
	}
	return bestMove;
}

int AI::minReturn(StateManager* statemanager, std::vector<std::vector<Entity*>> markerVec)
{
	if (gameOver(statemanager, markerVec)) return score(statemanager, markerVec);

	Moves duhbigmove;
	int bestMove = 1000;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (markerVec[i][j]->getId() == emptyMarker)					// if our cell is equal to empty
			{
				markerVec[i][j]->setId(aiMarker);		// 
				int tempMax = maxReturn(statemanager, markerVec);			// recursive function for min/max
				if (tempMax <= bestMove)
				{
					bestMove = tempMax;
					duhbigmove.x = i;
					duhbigmove.y = j;
				}
				markerVec[i][j]->setId(emptyMarker);						// reset our cell back to empty
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