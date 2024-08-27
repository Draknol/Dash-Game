
#include "Level.hpp"

Level::Level(const std::string& fileName)
{
	// Load Map
	sf::RenderStates r;
	m_renderStates["color"] = r;
	load(fileName);
}

Level::Level() 
{
	// Set Values to Default
	sf::RenderStates r;
	m_renderStates["color"] = r;
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
	int red1, green1, blue1, alpha1;
	int red2, green2, blue2, alpha2;
	int red3, green3, blue3, alpha3;
	float fontSize = 0;
	std::string textureKey;
	std::string fontKey;
	std::string destination;
	std::string text;
	std::string function;
	sf::Vector2f location;
	sf::RenderStates renderState;
	sf::Texture* texture;
	sf::Font* font{};

	/* Platforms & Decorations */

	std::string type;
	while (file >> type)
	{
		// Ignore Comments
		if (type[0] == '#' || type[0] == '/')
		{
			std::getline(file, type);
			continue;
		}

		if (type[0] == 't' || type[0] == 'B')
		{
			file >> position.x >> position.y
				 >> fontSize
				 >> fontKey
				 >> red1 >> green1 >> blue1 >> alpha1
				 >> red2 >> green2 >> blue2 >> alpha2;

			if (type[0] == 'B') {
				file >> red3 >> green3 >> blue3 >> alpha3
					 >> function;
			}

			std::getline(file, text);
			text = text.substr(1);
			if (type[1] == 'b') fontSize *= 16.0F;

			// Load & Store Font
			if (m_fonts.find(fontKey) == m_fonts.end())
			{
				font = new sf::Font;
				font->loadFromFile("Fonts/" + fontKey + ".ttf");
				m_fonts[fontKey] = font;
			}
		}
		else
		{
			// Get Info
			file >> position.x >> position.y
				>> size.x >> size.y
				>> textureKey;

			if (textureKey == "color")
			{
				file >> red1 >> green1 >> blue1 >> alpha1;
			}
			else
			{
				red1 = 255;
				green1 = 255;
				blue1 = 255;
				alpha1 = 255;
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
		}

		// Check Coordinate Type
		if (type[1] == 'b')
		{
			position *= 16.0F;
			size *= 16.0F;
		}

		if (type[0] == 't')
		{
			// Create Text
			if (font != nullptr)
			{
				m_texts.emplace_back(text, *font, (int) fontSize, position, sf::Color(red1, green1, blue1, alpha1), sf::Color(red2, green2, blue2, alpha2));
			}
		}
		else if (type[0] == 'B')
		{
			// Create Text
			if (font != nullptr)
			{
				m_buttons.emplace_back(text, *font, (int)fontSize, position, sf::Color(red1, green1, blue1, alpha1), sf::Color(red2, green2, blue2, alpha2), sf::Color(red3, green3, blue3, alpha3), function);
			}
		}
		else
		{
			// Create Block
			Block block(position, size, sf::Color(red1, green1, blue1, alpha1), textureKey);

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
		if (text.getBottomRight().x < wBottomRight.x &&
			text.getTopLeft().x > wTopLeft.x &&
			text.getBottomRight().y < wBottomRight.y &&
			text.getTopLeft().y > wTopLeft.y)
		{
			// Draw Text if on Screen
			window.draw(text);
		}
	}

	// Loop over Buttons
	for (Button& button : m_buttons)
	{
		// Check if Button is on Screen
		if (button.getBottomRight().x < wBottomRight.x &&
			button.getTopLeft().x > wTopLeft.x &&
			button.getBottomRight().y < wBottomRight.y &&
			button.getTopLeft().y > wTopLeft.y)
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
		if (mousePosition.x < button.getBottomRight().x &&
			mousePosition.x > button.getTopLeft().x &&
			mousePosition.y < button.getBottomRight().y &&
			mousePosition.y > button.getTopLeft().y)
		{
			if (press == true)
			{
				button.colorPressed();
				return "null";
			}
			return button.getFunction();
		}
	}

	return "null";
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