
#include "Block.hpp"

namespace engine
{

Block::Block() {}

Block::Block(
	const sf::Vector2f &position,
	const sf::Vector2f &size,
	const sf::Color &color,
	const std::string &textureKey,
	unsigned int frameCount,
	unsigned int frameRate
)
	: m_textureKey(textureKey), m_frameCount(frameCount), m_frameRate(frameRate)
{
	m_textureManager->loadKey(textureKey, frameCount);

	m_vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);

	sf::Vertex vertex;
	vertex.color = color;

	// Top-left corner
	vertex.position = position;
	vertex.texCoords = { 0.0F, 0.0F };
	m_vertices.append(vertex);

	// Bottom-left corner
	vertex.position = { position.x, position.y + size.y };
	vertex.texCoords = { 0.0F, size.y };
	m_vertices.append(vertex);

	// Top-right corner
	vertex.position = { position.x + size.x, position.y };
	vertex.texCoords = { size.x, 0.0F };
	m_vertices.append(vertex);

	// Bottom-right corner
	vertex.position = { position.x + size.x, position.y + size.y };
	vertex.texCoords = { size.x, size.y };
	m_vertices.append(vertex);
}

std::istream &operator>>(std::istream &is, Block &block)
{
	sf::Vector2f position, size;
	int frameCount, frameRate;
	std::string textureKey;
	is >> position.x >> position.y >> size.x >> size.y >> frameCount >> frameRate >> textureKey;

	sf::Color color = sf::Color::White;

	// Handle special case
	if (textureKey == "color")
	{
		int hex;
		is >> std::hex >> hex >> std::dec;
		color = (sf::Color)hex;
	}

	block = Block(position * 16.0F, size * 16.0F, color, textureKey, frameCount, frameRate);

	return is;
}

void Block::updateAnimations(float deltaTime)
{
	if (m_frameCount > 1U)
	{
		m_currentFrame += deltaTime * (float)m_frameRate;
		m_currentFrame = fmodf(m_currentFrame, (float)m_textureManager->getFrameCount(m_textureKey));
	}
}

void Block::flipHorizontally()
{
	std::swap(m_vertices[0].texCoords.x, m_vertices[2].texCoords.x);
	std::swap(m_vertices[1].texCoords.x, m_vertices[3].texCoords.x);
}

void Block::setTextureKey(const std::string &textureKey)
{
	m_textureKey = textureKey;
	m_frameCount = m_textureManager->getFrameCount(textureKey);
}

void Block::draw(sf::RenderTarget &target, sf::RenderStates /*states*/) const
{
	target.draw(
		m_vertices, m_textureManager->getRenderStates(m_textureKey, (unsigned int)m_currentFrame % m_frameCount)
	);
}

} // namespace engine