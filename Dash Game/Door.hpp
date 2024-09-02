#pragma once

#include "Block.hpp"

/// <summary>
/// Interactable block that loads a new level
/// </summary>
class Door : public Block
{
public:

	/// <summary>
	/// Constructor for Door
	/// </summary>
	/// <param name="block">Base block to draw</param>
	/// <param name="destination">Map to load on interact</param>
	/// <param name="location">Location of the other side of the door in the map</param>
	Door(const Block& block, const std::string& destination, const sf::Vector2f& location);

	/// <summary>
	/// Gets the map to go to
	/// </summary>
	/// <returns>The map to go to</returns>
	const std::string& getDestination();

	/// <summary>
	/// Gets the location of the other side of the door
	/// </summary>
	/// <returns>The location of the other side of the door</returns>
	const sf::Vector2f& getLocation();

private:

	const std::string m_destination;
	const sf::Vector2f m_location;

};