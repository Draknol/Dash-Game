#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Block : public sf::RectangleShape
{
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f size, float rotation);
private:
	sf::Texture m_texture;
};