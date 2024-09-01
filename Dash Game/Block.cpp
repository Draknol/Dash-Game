
#include "Block.hpp"

Block::Block() {}

Block::Block(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& texture, int frameCount, int frameRate)
	: m_texture(texture), m_frameCount(frameCount), m_frameRate(frameRate)
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

void Block::updateFrame(float deltaTime)
{
	m_currentFrame += deltaTime * (float)m_frameRate;
	m_currentFrame = fmodf(m_currentFrame, (float)m_frameCount);
}

const std::string& Block::getTexture() const
{
	return m_texture;
}

int Block::getFrameCount() const
{
	return m_frameCount;
}

int Block::getCurrentFrame() const
{
	return (int)m_currentFrame;
}