
#include "Level.hpp"

Level::Level(std::string fileName)
{
	// Load Marker Texture
	m_markerTexture.loadFromFile("Textures/Marker.png");
	m_markerState.texture = &m_markerTexture;

	// Load Flag Texture
	m_doorTexture.loadFromFile("Textures/Door.png");
	m_doorState.texture = &m_doorTexture;

	// Load Map
	load(fileName);
}

void Level::load(std::string fileName)
{
	// Save Level Name
	m_name = fileName;

	// Open File
	std::fstream file;
	file.open("Levels/" + m_name + ".map");

	// Save Spawn & Kill Height
	file >> m_spawn.x >> m_spawn.y
		 >> m_killHeight;

	// Create Variables
	sf::Vector2f position;
	sf::Vector2f size;
	int red, green, blue;
	std::string destination;

	/* Platforms */

	// Initialise Array
	file >> m_platformCount;
	delete[] m_platforms;
	m_platforms = new Block[m_platformCount];

	// Fill Array
	for (int i = 0; i < m_platformCount; i++)
	{
		// Get Info
		file >> position.x >> position.y
		     >> size.x >> size.y
			 >> red >> green >> blue;

		// Store In Array
		Block block(position, size, sf::Color(red, green, blue));
		m_platforms[i] = block;
	}

	/* Markers */

	// Initialise Array
	file >> m_markerCount;
	delete[] m_markers;
	m_markers = new Block[m_markerCount];

	// Fill Array
	for (int i = 0; i < m_markerCount; i++)
	{
		// Get Info
		file >> position.x >> position.y
			>> red >> green >> blue;

		// Store In Array
		Block block(position, sf::Vector2f(50, 50), sf::Color(red, green, blue));
		m_markers[i] = block;
	}

	/* Flags */

	// Initialise Array
	file >> m_doorCount;
	delete[] m_doors;
	delete[] m_doorDestinations;
	m_doors = new Block[m_doorCount];
	m_doorDestinations = new std::string[m_doorCount];

	// Fill Array
	for (int i = 0; i < m_doorCount; i++)
	{
		// Get Info
		file >> position.x >> position.y
			>> red >> green >> blue
			>> destination;

		// Store In Array
		Block block(position, sf::Vector2f(50, 100), sf::Color(red, green, blue));
		m_doors[i] = block;
		m_doorDestinations[i] = destination;
	}

	// Close File
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
	for (int i = 0; i < m_doorCount; i++)
	{
		// Check if Block is on Screen
		if (m_doors[i][3].position.x < wBottomRight.x &&
			m_doors[i][1].position.x > wTopLeft.x &&
			m_doors[i][1].position.y < wBottomRight.y &&
			m_doors[i][3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(m_doors[i], m_doorState);
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

Block* Level::getDoors()
{
	return m_doors;
}

int Level::getDoorCount()
{
	return m_doorCount;
}

std::string* Level::getDoorDestinations()
{
	return m_doorDestinations;
}

sf::Vector2f Level::getSpawn()
{
	return m_spawn;
}

float Level::getKillHeight()
{
	return m_killHeight;
}

const std::string& Level::getName()
{
	return m_name;
}