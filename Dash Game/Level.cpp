
#include "Level.hpp"

Level::Level(const std::string& fileName)
{
	// Load Map
	m_renderStates["color"] = sf::RenderStates();
	load(fileName);
}

Level::Level() 
{
	// Set Values to Default
	m_renderStates["color"] = sf::RenderStates();
	m_spawn = sf::Vector2f(0, 0);
	m_killHeight = INT_MIN;
}

void Level::erase() 
{
	// Delete all Blocks
	m_platforms.clear();
	m_decorations.clear();
	m_doors.clear();
	m_texts.clear();
	m_buttons.clear();

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
	uint32_t color = 0U;
	uint32_t backgroundColor = 0U;
	uint32_t pressedColor = 0U;
	float fontSize = 0.0F;
	std::string textureKey;
	std::string fontKey;
	std::string destination;
	std::string text;
	std::string function;
	sf::Vector2f location;
	sf::RenderStates renderState;
	sf::Texture* texture{};
	sf::Font* font = new sf::Font;

	// Read in file
	std::string type;
	while (file >> type)
	{
		// Ignore Comments
		if (type[0] == '#' || type[0] == '/')
		{
			std::getline(file, type);
			continue;
		}

		// Handle text and buttons
		if (type[0] == 't' || type[0] == 'B')
		{
			// Read in text info
			file >> position.x >> position.y
				 >> fontSize >> fontKey
				 >> std::hex >> color >> std::dec;

			// Read in button info
			if (type[0] == 'B') {
				file >> std::hex >> backgroundColor >> pressedColor >> std::dec
					 >> function;
			}

			// Read in text (without space infront)
			std::getline(file, text);
			text = text.substr(1);

			// Check if units are px or blocks
			if (type[1] == 'b')
			{
				position *= 16.0F;
				size *= 16.0F;
				fontSize *= 16.0F;
			}

			// Load and or store font
			if (m_fonts.find(fontKey) == m_fonts.end())
			{
				m_fonts[fontKey] = new sf::Font;
				m_fonts[fontKey]->loadFromFile("Fonts/" + fontKey + ".ttf");
			}
			font = m_fonts.at(fontKey);

			// Check what object to create
			if (type[0] == 't')
			{
				// Create Text
				m_texts.emplace_back(text, *font, (int)fontSize, position, fromHex(color));
			}
			else
			{
				// Create Button
				m_buttons.emplace_back(text, *font, (int)fontSize, position, fromHex(color), fromHex(backgroundColor), fromHex(pressedColor), function);
			}
		}
		// Handle blocks
		else
		{
			// Get block info
			file >> position.x >> position.y
				>> size.x >> size.y
				>> textureKey;

			// Check if units are px or blocks
			if (type[1] == 'b')
			{
				position *= 16.0F;
				size *= 16.0F;
			}

			// Handle plain color case
			if (textureKey == "color")
			{
				file >> std::hex >> color >> std::dec;
			}
			else
			{
				color = 0xFFFFFFFF;
			}

			// Load & Store Texture
			if (m_renderStates.find(textureKey) == m_renderStates.end())
			{
				texture = new sf::Texture;
				texture->loadFromFile("Textures/" + textureKey + ".png");
				texture->setRepeated(true);
				m_textures.push_back(texture);
				renderState.texture = &*m_textures.back();
				m_renderStates[textureKey] = renderState;
			}

			// Create Block
			Block block(position, size, fromHex(color), textureKey);

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
				if (type[1] == 'b') location *= 16.0F;
				m_doors.emplace_back(block, destination, location);
				break;
			default:
				break;
			}
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
	for (Block& platform : m_platforms)
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
	for (Block& decoration : m_decorations)
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
	for (Door& door : m_doors)
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

	// Loop over Text
	for (Text& text : m_texts)
	{
		// Check if Text is on Screen
		if (text.getTopLeft().x < wBottomRight.x &&
			text.getBottomRight().x > wTopLeft.x &&
			text.getTopLeft().y < wBottomRight.y &&
			text.getBottomRight().y > wTopLeft.y)
		{
			// Draw Text if on Screen
			window.draw(text);
		}
	}

	// Loop over Buttons
	for (Button& button : m_buttons)
	{
		// Check if Button is on Screen
		if (button.getTopLeft().x < wBottomRight.x &&
			button.getBottomRight().x > wTopLeft.x &&
			button.getTopLeft().y < wBottomRight.y &&
			button.getBottomRight().y > wTopLeft.y)
		{
			// Draw Button if on Screen
			window.draw(button);
		}
	}
}

std::string Level::checkButtons(sf::Vector2f mousePosition, bool press)
{
	for (Button& button : m_buttons)
	{
		if (press == false) button.setReleasedColor();

		if (mousePosition.x < button.getBottomRight().x &&
			mousePosition.x > button.getTopLeft().x &&
			mousePosition.y < button.getBottomRight().y &&
			mousePosition.y > button.getTopLeft().y)
		{
			if (press == true)
			{
				button.setPressedColor();
				return "null";
			}
			return button.getFunction();
		}
	}

	return "null";
}

sf::Color Level::fromHex(uint32_t hex)
{
	return sf::Color((hex >> 24) & 0xFF, (hex >> 16) & 0xFF, (hex >> 8) & 0xFF, hex & 0xFF);
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