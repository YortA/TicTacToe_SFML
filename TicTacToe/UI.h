#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Font.hpp"

class UI
{
private:
	// our button objs
	class Entity
		* playButton = nullptr,
		* restartButton = nullptr,
		* quitButton = nullptr;

	
public:
	UI();
	~UI();

	void create();
	void destroy();

	class Entity
		* createPlayButton(),
		* createRestartButton(),
		* createQuitButton();

};