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
	font = new sf::Font;

	if (!font->loadFromFile("Graphics/ChessType.ttf"))
	{
		// .ttf file didn't load (ERROR)
	}
}

void UI::destroy()
{
	delete playButton;
	delete restartButton;
	delete quitButton;

	delete font;
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

sf::Font* UI::getFont()
{
	return font;
}

// Pass and set our font
void UI::setFont(sf::Font& font)
{
	this->font = &font;
}

void UI::createScoreText(std::string str, int score, sf::Text* text)
{
	std::string outputtext = std::to_string(score);		// convert int to string text

	text->setFont(*font);
	text->setCharacterSize(50);
	//text->setFillColor(sf::Color::Magenta);
	text->setStyle(sf::Text::Style::Regular);
	text->setOutlineColor(sf::Color::White);
	text->setOutlineThickness(5);

	text->setString(str + outputtext);
}

void UI::createMsgText(std::string str, sf::Text* text)
{
	text->setFont(*font);
	text->setCharacterSize(150);
	//text->setFillColor(sf::Color::Magenta);
	text->setStyle(sf::Text::Style::Bold);
	text->setOutlineColor(sf::Color::Black);
	//text->setOutlineThickness(0);

	text->setString(str);
}