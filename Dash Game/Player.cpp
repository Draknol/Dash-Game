
#include "Player.hpp"

Player::Player(float x, float y)
	: Player(sf::Vector2f(x, y)) {}

Player::Player(sf::Vector2f position)
{
	m_texture.loadFromFile("Textures/Player.png");

	setTexture(m_texture);
	setPosition(position);
}