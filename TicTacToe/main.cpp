#include "GameState.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main()
{
	Game TestWindow("Test Window", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	while (TestWindow.isRunning())
	{
		TestWindow.update();
		TestWindow.render();
	}
}