#include "Window.h"
#include "WindowParams.h"
#include "SFML/Window/Event.hpp"

// Let's pass our pointer window params to use our settings in order to create a window
Window::Window(const char* id, int width, int height, bool fullscreen)
{
	windowparams = new WindowParams(id, width, height, fullscreen);

	create(windowparams);
}

Window::Window(WindowParams* windowparams)
{
	create(windowparams);
}

Window::~Window()
{
	delete windowparams;
	delete window;
}

//
//
//

void Window::create(WindowParams* windowparams)
{
	window = new sf::RenderWindow(sf::VideoMode(windowparams->getWidth(), windowparams->getHeight()),
		windowparams->getId(), 
		(windowparams->getFullscreen() ? sf::Style::Fullscreen : sf::Style::Default));		// if fullscreen true (Fullscreen), else leave as default.
}

// Destroy our window -- close the window and destroy all attached resources
void Window::destroy()
{
	window->close();
}

// Update and render
void Window::clear()
{
	window->clear(sf::Color::Black);
}

void Window::draw(sf::Drawable& drawable)
{
	window->draw(drawable);
}

void Window::display()
{
	window->display();
}

//
//
//

bool Window::isOpen()
{
	return window->isOpen();
}

bool Window::isFullscreen()
{
	return windowparams->getFullscreen();
}

sf::RenderWindow* Window::getWindow()
{
	return window;
}

unsigned int Window::getWidth()
{
	return window->getSize().x;
}

unsigned int Window::getHeight()
{
	return window->getSize().y;
}
//
//
//

// SFML event handler for inputs https://www.sfml-dev.org/tutorials/1.6/window-events.php
void Window::handleEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			break;
		case sf::Event::KeyReleased:
			break;
		case sf::Event::Closed:
			window->close();
		}
	}
}