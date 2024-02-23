
#include "Block.hpp"

Block::Block() {}

Block::Block(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	// Make into Quad
	setPrimitiveType(sf::Quads);

	// Set Corner Positions and Colors
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

	// Set Texture Corners
	(*this)[0].texCoords = sf::Vector2f(0, 0);
	(*this)[1].texCoords = sf::Vector2f(size.x, 0);
	(*this)[2].texCoords = size;
	(*this)[3].texCoords = sf::Vector2f(0, size.y);
}