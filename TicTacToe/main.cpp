#include "GameState.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
	Game TicTacToe("TicTacToe - A (not so) Fun Game!", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (TicTacToe.isRunning())
	{
		TicTacToe.update();
		TicTacToe.render();
	}
}