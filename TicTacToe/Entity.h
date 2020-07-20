#pragma once
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Entity
{
private:
	void create(std::string texture);		// pass a string to find our texture
	void destroy();

	// SFML specific classes
	sf::Texture* texture = nullptr;
	sf::RectangleShape* rect = nullptr;		// required so that Texture* texture can be set
	
public:
	Entity(std::string texture);
	~Entity();

	// SFML member functions
	sf::Texture* getTexture();
	sf::RectangleShape* getRect();
	sf::Vector2f getPosition();			// where we want to position the entity inside the axis
	sf::Vector2f getOrigin();			// Where the origin is in relation to the draw axis

	void setTexture(sf::Texture* texture);
	void setRect(sf::RectangleShape* rect);
	void setPosition(float x, float y);
	void setOrigin(float x, float y);
};