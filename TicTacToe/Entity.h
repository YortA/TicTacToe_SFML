#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Entity
{
private:
	void create(std::string texture);		// pass a string to find our texture
	//void create(std::string texture, class Window* window);
	void create(std::string texture, float width, float height, int spriterows, int spritecolumns);
	void destroy();

	// SFML specific classes
	sf::Texture* texture = nullptr;
	sf::RectangleShape* rect = nullptr;		// required so that Texture* texture can be set
	
public:
	Entity(std::string texture);
	Entity(std::string texture, float width, float height, int spriterows, int spritecolumns);		// spriterows/columns is for the sprite sheet
	~Entity();

	// SFML member functions
	sf::Texture* getTexture();
	sf::RectangleShape* getRect();
	sf::Vector2f getPosition();			// where we want to position the entity inside the axis
	sf::Vector2f getOrigin();			// Where the origin is in relation to the draw axis

	// Get Bounds (unsigned because our variable can't be negative)
	unsigned int getLeft();
	unsigned int getWidth();
	unsigned int getTop();
	unsigned int getHeight();


	// Non-SFML getters
	float getOpacity();

	// Non-SFML setters
	void setTexture(sf::Texture* texture);
	void setRect(sf::RectangleShape* rect);
	void setPosition(float x, float y);
	void setOrigin(float x, float y);
	void setOpacity(float x);
};