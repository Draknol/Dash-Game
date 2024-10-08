
#include "Level.hpp"

Level::Level(const std::string& fileName)
{
	// Load Map
	m_renderStates["color0"] = sf::RenderStates();
	load(fileName);
}

Level::Level() 
{
	// Set Values to Default
	m_renderStates["color0"] = sf::RenderStates();
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
	int frameCount = 0;
	int frameRate = 0;
	std::string textureKey;
	std::string fontKey;
	std::string destination;
	std::string text;
	std::string function;
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
				>> frameCount >> textureKey;

			// Get frame rate if animated
			if (frameCount > 1) file >> frameRate;

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
			if (m_renderStates.find(textureKey + "0") == m_renderStates.end()) {
				// Load sprite sheet
				sf::Texture* spriteSheet = new sf::Texture;
				spriteSheet->loadFromFile("Textures/" + textureKey + ".png");

				int frameWidth = spriteSheet->getSize().x / frameCount;
				int frameHeight = spriteSheet->getSize().y;

				for (int i = 0; i < frameCount; i++) {

					// Create frame
					sf::Texture* frame = new sf::Texture;
					frame->loadFromImage(spriteSheet->copyToImage(), sf::IntRect(i * frameWidth, 0, frameWidth, frameHeight));
					frame->setRepeated(true);

					// Store the texture
					m_textures.push_back(frame);

					// Set the render state for this frame
					renderState.texture = frame;
					m_renderStates[textureKey + std::to_string(i)] = renderState;
				}

				// Clean up the original full texture
				delete spriteSheet;
			}

			// Create Block
			Block block(position, size, fromHex(color), textureKey, frameCount, frameRate);

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
					>> position.x >> position.y;
				if (type[1] == 'b') position *= 16.0F;
				m_doors.emplace_back(block, destination, position);
				break;
			default:
				break;
			}
		}
	}

	// Close File
	file.close();
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

void Level::updateAnimations(float deltaTime)
{
	for (Block& platform : m_platforms)
	{
		platform.updateFrame(deltaTime);
	}

	// Loop over Markers
	for (Block& decoration : m_decorations)
	{
		decoration.updateFrame(deltaTime);
	}

	// Loop over Doors
	for (Door& door : m_doors)
	{
		door.updateFrame(deltaTime);
	}
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

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Get Window Bounds
	sf::Vector2f wTopLeft = target.mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f wBottomRight = target.mapPixelToCoords((sf::Vector2i)target.getSize());

	// Loop over Platforms
	for (const Block& platform : m_platforms)
	{
		// Check if Block is on Screen
		if (platform[3].position.x < wBottomRight.x &&
			platform[1].position.x > wTopLeft.x &&
			platform[1].position.y < wBottomRight.y &&
			platform[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			target.draw(platform, m_renderStates.at(platform.getTexture() + std::to_string(platform.getCurrentFrame())));
		}
	}

	// Loop over Markers
	for (const Block& decoration : m_decorations)
	{
		// Check if Block is on Screen
		if (decoration[3].position.x < wBottomRight.x &&
			decoration[1].position.x > wTopLeft.x &&
			decoration[1].position.y < wBottomRight.y &&
			decoration[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			target.draw(decoration, m_renderStates.at(decoration.getTexture() + std::to_string(decoration.getCurrentFrame())));
		}
	}

	// Loop over Doors
	for (const Door& door : m_doors)
	{
		// Check if Block is on Screen
		if (door[3].position.x < wBottomRight.x &&
			door[1].position.x > wTopLeft.x &&
			door[1].position.y < wBottomRight.y &&
			door[3].position.y > wTopLeft.y)
		{
			// Draw Block if on Screen
			target.draw(door, m_renderStates.at(door.getTexture() + std::to_string(door.getCurrentFrame())));
		}
	}

	// Loop over Text
	for (const Text& text : m_texts)
	{
		// Check if Text is on Screen
		if (text.getTopLeft().x < wBottomRight.x &&
			text.getBottomRight().x > wTopLeft.x &&
			text.getTopLeft().y < wBottomRight.y &&
			text.getBottomRight().y > wTopLeft.y)
		{
			// Draw Text if on Screen
			target.draw(text, states);
		}
	}

	// Loop over Buttons
	for (const Button& button : m_buttons)
	{
		// Check if Button is on Screen
		if (button.getTopLeft().x < wBottomRight.x &&
			button.getBottomRight().x > wTopLeft.x &&
			button.getTopLeft().y < wBottomRight.y &&
			button.getBottomRight().y > wTopLeft.y)
		{
			// Draw Button if on Screen
			target.draw(button, states);
		}
	}
}