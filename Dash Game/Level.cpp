
#include "Level.hpp"

Level::Level(std::string fileName)
{
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

	// Delete old map
	m_platforms.clear();
	m_decorations.clear();
	m_doors.clear();

	/* Platforms & Decorations */

	std::string type;
	while (file >> type)
	{
		// Ignore Comments
		if (type[0] == '#')
		{
			std::getline(file, type);
			continue;
		}

		// Get Info
		file >> position.x >> position.y
			>> size.x >> size.y
			>> red >> green >> blue;

		Block block(position, size, sf::Color(red, green, blue));

		// Store in Vector
		switch (type[0])
		{
		case 'p':
			m_platforms.push_back(block);
			break;
		case 'd':
			m_decorations.push_back(block);
			break;
		case 'D':
			m_doors.push_back(block);
			file >> destination;
			m_doorDestinations.push_back(destination);
			break;
		default:
			break;
		}
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
	for (Block platform : m_platforms)
	{
		// Check if Block is on Screen
		if (platform[3].position.x < wBottomRight.x &&
			platform[1].position.x > wTopLeft.x &&
			platform[1].position.y < wBottomRight.y &&
			platform[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(platform);
		}
	}

	// Loop over Markers
	for (Block decoration : m_decorations)
	{
		// Check if Block is on Screen
		if (decoration[3].position.x < wBottomRight.x &&
			decoration[1].position.x > wTopLeft.x &&
			decoration[1].position.y < wBottomRight.y &&
			decoration[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(decoration);
		}
	}

	// Loop over Doors
	for (Block door : m_doors)
	{
		// Check if Block is on Screen
		if (door[3].position.x < wBottomRight.x &&
			door[1].position.x > wTopLeft.x &&
			door[1].position.y < wBottomRight.y &&
			door[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(door, m_doorState);
		}
	}
}

std::vector<Block>& Level::getPlatforms()
{
	return m_platforms;
}

std::vector<Block>& Level::getDoors()
{
	return m_doors;
}

std::vector<std::string>& Level::getDoorDestinations()
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