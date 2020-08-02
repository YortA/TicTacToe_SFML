#include "Entity.h"
#include "Window.h"
#include "SFML/System/Vector2.hpp"


Entity::Entity(std::string texture)
{
	create(texture);
}

Entity::Entity(std::string texture, float width, float height, int spriterows, int spritecolumns)
{
	create(texture, width, height, spriterows, spritecolumns);
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
	// get our texture rect shape and size
	rect = new sf::RectangleShape(sf::Vector2f((float)this->texture->getSize().x, (float)this->texture->getSize().y));
	rect->setTexture(this->texture);
	rect->setOrigin(sf::Vector2f(this->texture->getSize().x / 2.0f, this->texture->getSize().y / 2.0f));
}

// use this to stretch sprite to texture size (i.e. marker on grid)
void Entity::create(std::string texture, float width, float height, int spriterows, int spritecolumns)
{
	this->texture = new sf::Texture;
	gridPosition = new sf::Vector2i;		// used to set/get our grid position	// currently deprecated (new method used in gamestate)

	this->texture->loadFromFile(texture);	// get our texture image
	rect = new sf::RectangleShape(sf::Vector2f(width, height));	// set our rect shape for this object
	rect->setTexture(this->texture);		// set rect to our texture we just imported
	
	// addition for uvRect -- we use this to get our sprite out of our sprite sheet. (X and O) see createEntities() in gamestate.cpp
	rect->setTextureRect(sf::IntRect(0, 0, this->texture->getSize().x / spriterows, this->texture->getSize().y / spritecolumns));
	// set our origin for the rect (0,0) by default
	rect->setOrigin(sf::Vector2f(this->texture->getSize().x / 2.0f, this->texture->getSize().y / 2.0f));
}

void Entity::destroy()
{
	delete texture;
	delete rect;
	delete gridPosition;
}

// getters for our SFML
// SEE https://www.sfml-dev.org/documentation/2.5.1/annotated.php
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

sf::Vector2i* Entity::getGridPosition()
{
	return gridPosition;
}

// getters for our non-SFML
float Entity::getOpacity()
{
	return rect->getFillColor().a;
}

unsigned int Entity::getLeft()
{
	return rect->getPosition().x + rect->getLocalBounds().left;				// 
}

unsigned int Entity::getWidth()
{
	return rect->getPosition().x + rect->getLocalBounds().width;
}

unsigned int Entity::getTop()
{
	return rect->getPosition().y + rect->getLocalBounds().top;
}

unsigned int Entity::getHeight()
{
	return rect->getPosition().y + rect->getLocalBounds().height;
}

char Entity::getId()
{
	return id;
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

// This will return our location in the grid for our entity [0][0] - [2][2] ([x][y])
void Entity::setGridPosition(int x, int y)
{
	gridPosition->x = x;
	gridPosition->y = y;
}

// Find our entity id (whether it's empty, x or o.)
void Entity::setId(char id)
{
	this->id = id;
}
