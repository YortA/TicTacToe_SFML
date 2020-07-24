#pragma once

// We need this to render our window
#include "SFML/Graphics/RenderWindow.hpp"

class Window
{
private:
	class WindowParams* windowparams = nullptr;
	sf::RenderWindow* window = nullptr;
public:
	Window(const char* id, int width, int height, bool fullscreen);
	Window(class WindowParams* windowparams);
	~Window();

	void create(class WindowParams* windowparams);
	void destroy();

	void clear();
	void draw(sf::Drawable& drawable);		// allows us to draw in the window
	void display();

	bool isOpen();					// check to see if our window is open
	bool isFullscreen();
	//void toggleFullscreen();

	// We don't 
	unsigned int getWidth();
	unsigned int getHeight();

	// our event handler for inputs
	void handleEvent();

	sf::RenderWindow* getWindow();
};