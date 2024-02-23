#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <fstream>

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
	Block* getPlatforms();

	/// <summary>
	/// Gets number of Platforms
	/// </summary>
	/// <returns>Number of Platforms</returns>
	int getPlatformCount();

	/// <summary>
	/// Gets array of Flags
	/// </summary>
	/// <returns>Pointer to Beginning of Array</returns>
	Block* getFlags();

	/// <summary>
	/// Gets number of Flags
	/// </summary>
	/// <returns>Number of Flags</returns>
	int getFlagCount();

	/// <summary>
	/// Gets Array of Flag Destinations (destination[i] is for flag[i])
	/// </summary>
	/// <returns>Pointer to Beginning of Array</returns>
	std::string* getFlagDestinations();

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

private:

	// Platforms
	Block* m_platforms = nullptr;
	int m_platformCount = 0;

	// Markers
	Block* m_markers = nullptr;
	sf::RenderStates m_markerState;
	sf::Texture m_markerTexture;
	int m_markerCount = 0;

	// Flags
	Block* m_flags = nullptr;
	std::string* m_flagDestinations = nullptr;
	sf::RenderStates m_flagState;
	sf::Texture m_flagTexture;
	int m_flagCount = 0;

	// Player
	sf::Vector2f m_spawn;
	float m_killHeight;

};