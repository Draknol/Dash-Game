
#include "Level.hpp"

Level::Level(std::string fileName)
{
	load(fileName);
}

void Level::load(std::string fileName)
{
	std::fstream file;
	file.open("Levels/" + fileName + ".map");

	file >> m_spawn.x >> m_spawn.y
		 >> m_killHeight;

	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;

	file >> m_blockCount;
	m_blocks = new Block[m_blockCount];

	for (int i = 0; i < m_blockCount; i++)
	{
		file >> position.x >> position.y
		     >> size.x >> size.y
			 >> color.r >> color.g >> color.b;

		Block block(position, size, color);
		m_blocks[i] = block;
	}
}

void Level::draw(sf::RenderWindow& window)
{
	// Get Window Bounds
	sf::Vector2f wTopLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f wBottomRight = window.mapPixelToCoords((sf::Vector2i)window.getSize());

	// Loop over Blocks
	for (int i = 0; i < m_blockCount; i++)
	{
		// Check if Block is on Screen
		if (m_blocks[i][3].position.x < wBottomRight.x && 
			m_blocks[i][1].position.x > wTopLeft.x && 
			m_blocks[i][1].position.y < wBottomRight.y && 
			m_blocks[i][3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(m_blocks[i]);
		}
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

sf::Vector2f Level::getSpawn()
{
	return m_spawn;
}

float Level::getKillHeight()
{
	return m_killHeight;
}