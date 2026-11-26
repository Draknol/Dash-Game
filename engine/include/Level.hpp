#pragma once

#include "BlockManager.hpp"
#include "Door.hpp"

#include <fstream>

namespace engine
{

/// <summary>
/// Level class that stores Blocks loaded from a level
/// </summary>
class Level : public sf::Drawable
{
  public:

	Level();

	Level(const std::string &fileName);

	void clear();

	/// <summary>
	/// load new .map
	/// </summary>
	/// <param name="fileName">name of .map file (without .map)</param>
	void load(std::string fileName);

	void updateAnimations(float deltaTime);

	/// <summary>
	/// Gets all Blocks with collision
	/// </summary>
	const BlockManager<Block> &getPlatforms() const { return m_platforms; }

	/// <summary>
	/// Gets all Blocks without collision
	/// </summary>
	const BlockManager<Block> &getDecorations() const { return m_decorations; }

	const BlockManager<Door> &getDoors() const { return m_doors; }

	const sf::Vector2f &getSpawn() const { return m_spawn; }

  protected:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:

	std::string m_name;

	BlockManager<Block> m_platforms;   // collision
	BlockManager<Block> m_decorations; // no collision
	BlockManager<Door> m_doors;

	sf::Vector2f m_spawn = { 0.0F, 0.0F };
};

} // namespace engine