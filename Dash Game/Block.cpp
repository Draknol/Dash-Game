
#include "Block.hpp"

Block::Block() {}

Block::Block(sf::Vector2f position, sf::Vector2f size)
	: m_size(size)
{
	
	setPrimitiveType(sf::Quads);

	sf::Vertex vertex;
	vertex.position = position;
	append(vertex);
	vertex.position = position + sf::Vector2f(m_size.x, 0.0F);
	append(vertex);
	vertex.position = position + sf::Vector2f(m_size.x, m_size.y);
	append(vertex);
	vertex.position = position + sf::Vector2f(0.0F, m_size.y);
	append(vertex);
}

sf::Vector2f Block::getSize()
{
	return m_size;
}