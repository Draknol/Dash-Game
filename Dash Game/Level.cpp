
#include "Level.hpp"

Level::Level(std::string fileName)
{
	m_markerTexture.loadFromFile("Textures/Marker.png");
	m_markerState.texture = &m_markerTexture;
	m_flagTexture.loadFromFile("Textures/Flag.png");
	m_flagState.texture = &m_flagTexture;
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
	std::string destination;

	file >> m_platformCount;
	delete[] m_platforms;
	m_platforms = new Block[m_platformCount];

	for (int i = 0; i < m_platformCount; i++)
	{
		file >> position.x >> position.y
		     >> size.x >> size.y
			 >> color.r >> color.g >> color.b;

		Block block(position, size, color);
		m_platforms[i] = block;
	}

	file >> m_markerCount;
	delete[] m_markers;
	m_markers = new Block[m_markerCount];

	for (int i = 0; i < m_markerCount; i++)
	{
		file >> position.x >> position.y
			>> color.r >> color.g >> color.b;

		Block block(position, sf::Vector2f(50, 50), color);
		m_markers[i] = block;
	}

	file >> m_flagCount;
	delete[] m_flags;
	delete[] m_flagDestinations;
	m_flags = new Block[m_flagCount];
	m_flagDestinations = new std::string[m_flagCount];

	for (int i = 0; i < m_flagCount; i++)
	{
		file >> position.x >> position.y
			 >> destination;

		Block block(position, sf::Vector2f(50, 100), sf::Color::White);
		m_flags[i] = block;
		m_flagDestinations[i] = destination;
	}

	file.close();
}

void Level::draw(sf::RenderWindow& window)
{
	// Get Window Bounds
	sf::Vector2f wTopLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f wBottomRight = window.mapPixelToCoords((sf::Vector2i)window.getSize());

	// Loop over Platforms
	for (int i = 0; i < m_platformCount; i++)
	{
		// Check if Block is on Screen
		if (m_platforms[i][3].position.x < wBottomRight.x && 
			m_platforms[i][1].position.x > wTopLeft.x && 
			m_platforms[i][1].position.y < wBottomRight.y && 
			m_platforms[i][3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(m_platforms[i]);
		}
	}

	// Loop over Markers
	for (int i = 0; i < m_markerCount; i++)
	{
		// Check if Block is on Screen
		if (m_markers[i][3].position.x < wBottomRight.x &&
			m_markers[i][1].position.x > wTopLeft.x &&
			m_markers[i][1].position.y < wBottomRight.y &&
			m_markers[i][3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(m_markers[i], m_markerState);
		}
	}

	// Loop over Flags
	for (int i = 0; i < m_flagCount; i++)
	{
		// Check if Block is on Screen
		if (m_flags[i][3].position.x < wBottomRight.x &&
			m_flags[i][1].position.x > wTopLeft.x &&
			m_flags[i][1].position.y < wBottomRight.y &&
			m_flags[i][3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(m_flags[i], m_flagState);
		}
	}
}

Block* Level::getPlatforms()
{
	return m_platforms;
}

int Level::getPlatformCount()
{
	return m_platformCount;
}

Block* Level::getFlags()
{
	return m_flags;
}

int Level::getFlagCount()
{
	return m_flagCount;
}

std::string* Level::getFlagDestinations()
{
	return m_flagDestinations;
}

sf::Vector2f Level::getSpawn()
{
	return m_spawn;
}

float Level::getKillHeight()
{
	return m_killHeight;
}