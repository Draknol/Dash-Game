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
	Block* getDoors();

	/// <summary>
	/// Gets number of Flags
	/// </summary>
	/// <returns>Number of Flags</returns>
	int getDoorCount();

	/// <summary>
	/// Gets Array of Flag Destinations (destination[i] is for flag[i])
	/// </summary>
	/// <returns>Pointer to Beginning of Array</returns>
	std::string* getDoorDestinations();

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

	// Platforms
	Block* m_platforms = nullptr;
	int m_platformCount = 0;

	// Markers
	Block* m_markers = nullptr;
	sf::RenderStates m_markerState;
	sf::Texture m_markerTexture;
	int m_markerCount = 0;

	// Flags
	Block* m_doors = nullptr;
	std::string* m_doorDestinations = nullptr;
	sf::RenderStates m_doorState;
	sf::Texture m_doorTexture;
	int m_doorCount = 0;

	// Player
	sf::Vector2f m_spawn;
	float m_killHeight;

};