#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Font.hpp"

class UI
{
private:


public:
	UI();
	~UI();

	sf::RectangleShape* createMenuBox(sf::Font* font, int width, int height, int posx, int posy, const char* message);
	sf::Font* createFont(const char* fileLocation);


};