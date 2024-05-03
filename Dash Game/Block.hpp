#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Block : public sf::VertexArray
{
public:
	/// <summary>
	/// Constructor for Block
	/// </summary>
	Block();

	/// <summary>
	/// Constructor for Block
	/// </summary>
	/// <param name="position">Top Left of Block</param>
	/// <param name="size">Width and Height of Block</param>
	/// <param name="color">Color of Block</param>
	/// /// <param name="texture">Name of Texture File ("null" for no texture)</param>
	Block(sf::Vector2f position, sf::Vector2f size, sf::Color color, std::string texture);

	std::string getTexture();

	void setDestination(const std::string& destination);

	const std::string& getDestination();
private:

	std::string m_destination;
	std::string m_texture;
};