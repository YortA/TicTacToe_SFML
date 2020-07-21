#include "Entity.h"
#include "SFML/System/Vector2.hpp"


Entity::Entity(std::string texture)
{
	create(texture);
}

Entity::~Entity()
{
	destroy();
}

//
//
//

void Entity::create(std::string texture)
{
	this->texture = new sf::Texture;		// we have to use this-> because we're referencing the member out of scope

	this->texture->loadFromFile(texture);	// pass our argument to load a specific texture
	rect = new sf::RectangleShape(sf::Vector2f((float)this->texture->getSize().x, (float)this->texture->getSize().y));
	rect->setTexture(this->texture);
	rect->setOrigin(sf::Vector2f(this->texture->getSize().x / 2.0f, this->texture->getSize().y / 2.0f));
}

void Entity::destroy()
{
	delete texture;
	delete rect;
}

// getters for our SFML
sf::Texture* Entity::getTexture()
{
	return texture;
}

sf::RectangleShape* Entity::getRect()
{
	return rect;
}

sf::Vector2f Entity::getPosition()
{
	return rect->getPosition();
}

sf::Vector2f Entity::getOrigin()
{
	return rect->getOrigin();
}

// getters for our non-SFML
float Entity::getOpacity()
{
	return rect->getFillColor().a;
}


// Setters
void Entity::setTexture(sf::Texture* texture)
{
	this->texture = texture;
}

void Entity::setRect(sf::RectangleShape* rect)
{
	this->rect = rect;
}
void Entity::setPosition(float x, float y)
{
	rect->setPosition(x, y);
}

void Entity::setOrigin(float x, float y)
{
	rect->setOrigin(sf::Vector2f(x, y));
}

void Entity::setOpacity(float x)
{
	rect->setFillColor(sf::Color(			// pass our alpha value
		rect->getFillColor().r,
		rect->getFillColor().g,
		rect->getFillColor().b,
		x));
}
