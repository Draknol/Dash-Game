
#include "Level.hpp"

Level::Level(std::string fileName)
{
	std::fstream file;
	file.open("Levels/" + fileName + ".wld");

	sf::Vector2f position;
	sf::Vector2f size;

	file >> m_blockCount;
	m_blocks = new Block[m_blockCount];

	for (int i = 0; i < m_blockCount; i++)
	{
		file >> position.x;
		file >> position.y;
		file >> size.x;
		file >> size.y;

		Block block(position, size);
		m_blocks[i] = block;
	}
}

void Level::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < m_blockCount; i++)
	{
		window.draw(m_blocks[i]);
	}
}

Block* Level::getBlocks()
{
	return m_blocks;
}

int Level::getBlockCount()
{
	return m_blockCount;
}