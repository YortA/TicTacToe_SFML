#pragma once


class WindowParams
{
private:
	const char* id;
	int	width;
	int	height;
	bool fullscreen;

public:
	// Access members so we can get the private values
	const char* getId() { return id; }
	int getWidth() { return width; }
	int	getHeight() { return height; }
	bool getFullscreen() { return fullscreen; }

	// Set our private values
	void setId(const char* id) { this->id = id; }
	void setWidth(int width) { this->width = width; }
	void setHeight(int height) { this->height = height; }
	void setFullscreen(bool fullscreen) { this->fullscreen = fullscreen; }

	// Constructors/Destructors
	WindowParams();
	WindowParams(const char* id, int width, int height, bool fullscreen);
	~WindowParams();	
};