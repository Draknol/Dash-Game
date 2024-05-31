
#include "Level.hpp"

Level::Level(const std::string& fileName)
{
	// Load Map
	sf::RenderStates r;
	m_renderStates["null"] = r;
	load(fileName);
}

Level::Level() 
{
	// Set Values to Default
	sf::RenderStates r;
	m_renderStates["null"] = r;
	m_spawn = sf::Vector2f(0, 0);
	m_killHeight = INT_MIN;
}

void Level::erase() 
{
	// Delete all Blocks
	m_platforms.clear();
	m_decorations.clear();
	m_doors.clear();

	// Set Values to Default
	m_spawn = sf::Vector2f(0, 0);
	m_killHeight = INT_MIN;
}

void Level::load(const std::string& fileName)
{
	// Delete old Map
	erase();

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
	std::string textureKey;
	std::string destination;
	sf::Vector2f location;
	sf::RenderStates renderState;
	sf::Texture* texture;

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
			>> red >> green >> blue
			>> textureKey;

		// Create Block
		Block block(position, size, sf::Color(red, green, blue), textureKey);

		// Load & Store Texture
		if (m_renderStates.find(textureKey) == m_renderStates.end())
		{
			texture = new sf::Texture;
			texture->loadFromFile("Textures/" + textureKey + ".png");
			texture->setRepeated(true);
			textures.push_back(texture);
			renderState.texture = &*textures.back();
			m_renderStates[textureKey] = renderState;
		}

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
			file >> destination
				 >> location.x >> location.y;
			m_doors.emplace_back(block, destination, location);
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
			window.draw(platform, m_renderStates.at(platform.getTexture()));
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
			window.draw(decoration, m_renderStates.at(decoration.getTexture()));
		}
	}

	// Loop over Doors
	for (auto door : m_doors)
	{
		// Check if Block is on Screen
		if (door[3].position.x < wBottomRight.x &&
			door[1].position.x > wTopLeft.x &&
			door[1].position.y < wBottomRight.y &&
			door[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			window.draw(door, m_renderStates.at(door.getTexture()));
		}
	}
}

const std::vector<Block>& Level::getPlatforms()
{
	return m_platforms;
}

const std::vector<Door>& Level::getDoors()
{
	return m_doors;
}

const sf::Vector2f& Level::getSpawn()
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