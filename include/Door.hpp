#pragma once

#include "Block.hpp"

/// <summary>
/// Extends Block
/// stores Level name and location of the other side of the Door
/// </summary>
class Door : public Block
{
public:
	
	Door();

	Door(const Block& block, const std::string& levelName, const sf::Vector2f& levelSpawn);

	friend std::istream& operator>>(std::istream& is, Door& door);

	const std::string& getLevelName() const;

	const sf::Vector2f& getLevelSpawn() const;

private:

	std::string levelName;
	sf::Vector2f levelSpawn;

};