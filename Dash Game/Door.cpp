#include "Door.hpp"

Door::Door()
{
}

Door::Door(const Block& block, const std::string& levelName, const sf::Vector2f& levelSpawn)
	: Block(block), levelName(levelName), levelSpawn(levelSpawn)
{
}

std::istream& operator>>(std::istream& is, Door& door)
{
	Block block;
	std::string levelName;
	sf::Vector2f levelSpawn;
	is >> block
		>> levelName
		>> levelSpawn.x >> levelSpawn.y;

	door = Door(block, levelName, levelSpawn * 16.0F);

	return is;
}


const std::string& Door::getLevelName() const
{
	return levelName;
}

const sf::Vector2f& Door::getLevelSpawn() const
{
	return levelSpawn;
}

