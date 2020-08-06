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

	//sf::Font* font = nullptr;
	//sf::Text* text = nullptr;

public:
	UI();
	~UI();

	void create();
	void destroy();

	class Entity
		* createPlayButton(),
		* createRestartButton(),
		* createQuitButton();

	void createText(int score);

};