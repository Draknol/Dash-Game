#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <unordered_map>
#include <fstream>
#include <vector>

#include "Block.hpp"
#include "Door.hpp"

class Level
{
public:

	/// <summary>
	/// Constructor for Level
	/// </summary>
	/// <param name="fileName">Name of .map file</param>
	Level(const std::string& fileName);

	/// <summary>
	/// Constructor for Level
	/// </summary>
	Level();

	/// <summary>
	/// Unload Map/Load Blank Map (not textures)
	/// </summary>
	void erase();

	/// <summary>
	/// Load new Map
	/// </summary>
	/// <param name="fileName">Name of .map file</param>
	void load(const std::string& fileName);

	/// <summary>
	/// Draw Blocks to Window
	/// </summary>
	/// <param name="window">Window to draw to</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Gets Platforms Vector
	/// </summary>
	/// <returns>Vector of Platforms</returns>
	const std::vector<Block>& getPlatforms();

	/// <summary>
	/// Gets Doors Vector
	/// </summary>
	/// <returns>Gets Vector of Doors</returns>
	const std::vector<Door>& getDoors();

	/// <summary>
	/// Gets Spawn Point for the Current Map
	/// </summary>
	/// <returns>Spawn Point for the Current Map</returns>
	const sf::Vector2f& getSpawn();

	/// <summary>
	/// Gets Kill Height for the Current Map
	/// </summary>
	/// <returns>Kill Height for the Current Map</returns>
	float getKillHeight();

	/// <summary>
	/// Gets Name of the Current Map
	/// </summary>
	/// <returns></returns>
	const std::string& getName();

private:

	// Level
	std::string m_name;

	// Blocks
	std::vector<Block> m_platforms;
	std::vector<Block> m_decorations;
	std::vector<Door> m_doors;

	// Player
	sf::Vector2f m_spawn;
	float m_killHeight;

	// Textures
	std::unordered_map<std::string, sf::RenderStates> m_renderStates;
	std::vector<sf::Texture*> textures;
};