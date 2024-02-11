
#include "Player.hpp"

Player::Player(float x, float y) : Player(sf::Vector2f(x, y)) {}

Player::Player(const sf::Vector2f &position) : m_position(position)
{
	// Load Player Texture
	m_texture.loadFromFile("Textures/Player.png");

	// Set Sprite Defaults
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
}

void Player::setPosition(const sf::Vector2f &position)
{
	m_position = position;
}

void Player::setPosition(float x, float y)
{
	m_position = sf::Vector2f(x, y);
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}