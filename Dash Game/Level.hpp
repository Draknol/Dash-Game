#pragma once

#include "Door.hpp"
#include "BlockManager.hpp"
#include <fstream>

/// <summary>
/// Level class that stores Blocks loaded from a level
/// </summary>
class Level : public sf::Drawable
{
public:

	Level();

	Level(const std::string& fileName);

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
	const BlockManager<Block>& getPlatforms() const;

	/// <summary>
	/// Gets all Blocks without collision
	/// </summary>
	const BlockManager<Block>& getDecorations() const;

	const BlockManager<Door>& getDoors() const;

	const sf::Vector2f& getSpawn() const;

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	std::string name;

	BlockManager<Block> platforms; // collision
	BlockManager<Block> decorations; // no collision
	BlockManager<Door> doors;

	sf::Vector2f spawn = {0.0F, 0.0F};

};