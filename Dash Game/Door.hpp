#include "Block.hpp"

class Door : public Block
{
public:
	Door(const Block& block, const std::string& destination, const sf::Vector2f& location);

	const std::string& getDestination();

	const sf::Vector2f& getLocation();

private:
	const std::string m_destination;
	const sf::Vector2f m_location;
};