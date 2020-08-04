#include "UI.h"
#include "Entity.h"

UI::UI()
{
	create();
}

UI::~UI()
{
	destroy();
}

void UI::create()
{
	playButton = new Entity("Graphics/play_button.png");
	restartButton = new Entity("Graphics/restart_button.png");
	quitButton = new Entity("Graphics/quit_button.png");
}

void UI::destroy()
{
	delete playButton;
	delete restartButton;
	delete quitButton;
}

Entity* UI::createPlayButton()
{
	return playButton;
}

Entity* UI::createRestartButton()
{
	return restartButton;
}

Entity* UI::createQuitButton()
{
	return quitButton;
}
