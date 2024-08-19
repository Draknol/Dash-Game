#include "Door.hpp"

Door::Door(const Block& block, const std::string& destination, const sf::Vector2f& location) : Block(block), m_destination(destination), m_location(location) {}

const std::string& Door::getDestination()
{
	return m_destination;
}

const sf::Vector2f& Door::getLocation()
{
	return m_location;
}