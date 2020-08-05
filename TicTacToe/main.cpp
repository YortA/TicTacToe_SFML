// Troy Andrews
// 7/18/2020
// TicTacToe using SFML

// Refernces for setting up SFML Game Development by Example (eBook)
// SFML: https://www.sfml-dev.org/documentation/2.5.1/index.php

#include "Game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
	Game* TicTacToe = new Game { "TicTacToe - A (not so) Fun Game!", SCREEN_WIDTH, SCREEN_HEIGHT, false };

	while (TicTacToe->isRunning())
	{
		TicTacToe->update();
		TicTacToe->render();
	}
}


// BUG LIST

// we need to prevent changing states when clicking on an existing entity. this way the AI doesn't get an extra turn. (see gamestate.cpp)