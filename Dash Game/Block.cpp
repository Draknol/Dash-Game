
#include "Block.hpp"

Block::Block() {}

Block::Block(sf::Vector2f position, sf::Vector2f size, float rotation)
{
	setPosition(position);
	setSize(size);
	setRotation(rotation);
}