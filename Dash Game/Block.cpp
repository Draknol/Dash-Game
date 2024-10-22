
#include "Block.hpp"

Block::Block()
{
}

Block::Block(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& textureKey, int frameCount, int frameRate)
	: textureKey(textureKey), frameCount(frameCount), frameRate(frameRate)
{
	textureManager->loadKey(textureKey, frameCount);

	vertices.setPrimitiveType(sf::TrianglesStrip);

	sf::Vertex vertex;
	vertex.color = color;

	// Top-left corner
	vertex.position = position;
	vertex.texCoords = { 0, 0 };
	vertices.append(vertex);

	// Bottom-left corner
	vertex.position = { position.x, position.y + size.y };
	vertex.texCoords = { 0, size.y };
	vertices.append(vertex);

	// Top-right corner
	vertex.position = { position.x + size.x, position.y };
	vertex.texCoords = { size.x, 0 };
	vertices.append(vertex);

	// Bottom-right corner
	vertex.position = { position.x + size.x, position.y + size.y };
	vertex.texCoords = { size.x, size.y };
	vertices.append(vertex);
}

std::istream& operator>>(std::istream& is, Block& block)
{
	sf::Vector2f position, size;
	int frameCount, frameRate;
	std::string textureKey;
	is >> position.x >> position.y
		>> size.x >> size.y
		>> frameCount >> frameRate
		>> textureKey;

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
	if (frameCount > 1)
	{
		currentFrame += deltaTime * (float)frameRate;
		currentFrame = fmodf(currentFrame, (float)textureManager->getFrameCount(textureKey));
	}
}

float Block::getLeft() const
{
	return vertices[0].position.x;
}

float Block::getRight() const
{
	return vertices[3].position.x;
}

float Block::getTop() const
{
	return vertices[0].position.y;
}

float Block::getBottom() const
{
	return vertices[3].position.y;
}

void Block::flipHorizontally()
{
	std::swap(vertices[0].texCoords.x, vertices[2].texCoords.x);
	std::swap(vertices[1].texCoords.x, vertices[3].texCoords.x);
}

sf::Vertex& Block::getVertex(size_t index)
{
	return vertices[index];
}

void Block::setTextureKey(const std::string& textureKey)
{
	this->textureKey = textureKey;
	frameCount = textureManager->getFrameCount(textureKey);
}

void Block::setFrameRate(int frameRate)
{
	this->frameRate = frameRate;
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(vertices, textureManager->getRenderStates(textureKey, (int)currentFrame % frameCount));
}
