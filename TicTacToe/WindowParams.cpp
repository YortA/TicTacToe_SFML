#include "WindowParams.h"

// passed into our window.cpp function. gives the parameters for our window -- we can use this later to have resolution options
WindowParams::WindowParams(const char* id, int width, int height, bool fullscreen)
	: id(id),
	width(width),
	height(height),
	fullscreen(fullscreen)
{

}

// Default constructor incase our values didn't register
WindowParams::WindowParams()
	: id("NoID"),
	width(800),
	height(600),
	fullscreen(false)
{

}

// D E S T R O Y
WindowParams::~WindowParams()
{

}