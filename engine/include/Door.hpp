#pragma once

#include "Block.hpp"

namespace engine
{

/// <summary>
/// Extends Block
/// stores Level name and location of the other side of the Door
/// </summary>
class Door : public Block
{
  public:

	Door();

	Door(const Block &block, const std::string &levelName, const sf::Vector2f &levelSpawn);

	friend std::istream &operator>>(std::istream &is, Door &door);

	const std::string &getLevelName() const { return m_levelName; }

	const sf::Vector2f &getLevelSpawn() const { return m_levelSpawn; }

  private:

	std::string m_levelName;
	sf::Vector2f m_levelSpawn;
};

} // namespace engine