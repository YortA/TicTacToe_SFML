#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class UI
{
private:
	// our button objs
	class Entity
		* playButton = nullptr,
		* restartButton = nullptr,
		* quitButton = nullptr;

	// our text objs
	sf::Font* font = nullptr;

public:
	UI();
	~UI();

	void create();
	void destroy();
	
	// Buttons
	class Entity
		* createPlayButton(),
		* createRestartButton(),
		* createQuitButton();

	sf::Font* getFont();

	void setFont(sf::Font& font);
	void createScoreText(std::string str, int score, sf::Text* text);
	void createMsgText(std::string str, sf::Text* text);
};