#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <fstream>
#include <vector>

#include "Block.hpp"

class Level
{
public:

	/// <summary>
	/// Constructor for Level
	/// </summary>
	/// <param name="fileName">Name of .map file</param>
	Level(std::string fileName);

	/// <summary>
	/// Load new Map
	/// </summary>
	/// <param name="fileName">Name of .map file</param>
	void load(std::string fileName);

	/// <summary>
	/// Draw Blocks to Window
	/// </summary>
	/// <param name="window">Window to draw to</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Gets array of Platforms
	/// </summary>
	/// <returns>Pointer to Beginning of Array</returns>
	std::vector<Block>& getPlatforms();

	/// <summary>
	/// Gets array of Doors
	/// </summary>
	/// <returns>Pointer to Beginning of Array</returns>
	std::vector<Block>& getDoors();

	/// <summary>
	/// Gets Array of Door Destinations (destinations[i] is for doors[i])
	/// </summary>
	/// <returns>Pointer to Beginning of Array</returns>
	std::vector<std::string>& getDoorDestinations();

	/// <summary>
	/// Gets Spawn Point for the Current Map
	/// </summary>
	/// <returns>Spawn Point for the Current Map</returns>
	sf::Vector2f getSpawn();

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
	std::vector<Block> m_doors;
	std::vector<std::string> m_doorDestinations;

	// Textures
	sf::RenderStates m_doorState;
	sf::Texture m_doorTexture;

	// Player
	sf::Vector2f m_spawn;
	float m_killHeight;

};