#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/System/Vector2.hpp>

class Block : public sf::VertexArray
{
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f size, sf::Color color);
};