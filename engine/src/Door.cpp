#include "Door.hpp"

namespace engine
{

Door::Door() {}

Door::Door(const Block &block, const std::string &levelName, const sf::Vector2f &levelSpawn)
	: Block(block), m_levelName(levelName), m_levelSpawn(levelSpawn)
{
}

std::istream &operator>>(std::istream &is, Door &door)
{
	Block block;
	std::string levelName;
	sf::Vector2f levelSpawn;
	is >> block >> levelName >> levelSpawn.x >> levelSpawn.y;

	door = Door(block, levelName, levelSpawn * 16.0F);

	return is;
}

} // namespace engine