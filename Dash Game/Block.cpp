
#include "Block.hpp"

Block::Block() {}

Block::Block(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	setPrimitiveType(sf::Quads);

	sf::Vertex vertex;
	vertex.color = color;
	vertex.position = position;
	append(vertex);
	vertex.position = position + sf::Vector2f(size.x, 0.0F);
	append(vertex);
	vertex.position = position + size;
	append(vertex);
	vertex.position = position + sf::Vector2f(0.0F, size.y);
	append(vertex);
}