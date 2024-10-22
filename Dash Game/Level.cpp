
#include "Level.hpp"

Level::Level()
{
}

Level::Level(const std::string& fileName)
{
	load(fileName);
}

void Level::clear()
{
	name = "";
	platforms.clear();
	decorations.clear();
	doors.clear();
	spawn = { 0.0F, 0.0F };
}

void Level::load(std::string fileName)
{
	clear();
	name = fileName;

	std::fstream file;
	file.open("Levels/" + name + ".map");

	file >> spawn.x >> spawn.y;

	std::string type;
	while (file >> type)
	{
		switch (type[0])
		{
		case '#':
			std::getline(file, type);
			break;
		case 'p':
			platforms.push_back(Block());
			file >> platforms.back();
			break;
		case 'd':
			decorations.push_back(Block());
			file >> decorations.back();
			break;
		case 'D':
			doors.push_back(Door());
			file >> doors.back();
			break;
		default:
			break;
		}
	}
}

void Level::updateAnimations(float deltaTime)
{
	platforms.updateAnimations(deltaTime);
	decorations.updateAnimations(deltaTime);
	doors.updateAnimations(deltaTime);
}

const BlockManager<Block>& Level::getPlatforms() const
{
	return platforms;
}

const BlockManager<Block>& Level::getDecorations() const
{
	return decorations;
}

const BlockManager<Door>& Level::getDoors() const
{
	return doors;
}

const sf::Vector2f& Level::getSpawn() const
{
	return spawn;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(platforms, states);
	target.draw(decorations, states);
	target.draw(doors, states);
}
