#include "UI.h"
#include "Entity.h"
#include <string>

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
	//font = new sf::Font;
	//text = new sf::Text;
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


//void UI::createText(int score)
//{
//	if (!font->loadFromFile("Graphics/ChessType.ttf"))
//	{
//		// .ttf file didn't load (ERROR)
//	}
//
//	std::string outputtext = std::to_string(score);
//
//	text->setFont(*font);
//	text->setCharacterSize(50);
//	text->setFillColor(sf::Color::Magenta);
//	text->setStyle(sf::Text::Style::Bold);
//	text->setOutlineColor(sf::Color::White);
//	text->setOutlineThickness(5);
//
//	text->setString(outputtext);
//}
