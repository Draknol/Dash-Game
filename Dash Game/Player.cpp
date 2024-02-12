
#include "Player.hpp"

Player::Player(float x, float y)
	: Player(sf::Vector2f(x, y)) {}

Player::Player(sf::Vector2f position)
{
	m_texture.loadFromFile("Textures/Player.png");

	setTexture(m_texture);
	setPosition(position);
}

void Player::update(float deltaTime)
{
	m_velocity.x = m_speed * (m_movingRight - m_movingLeft);
	setPosition(getPosition() + m_velocity * deltaTime);
}

void Player::movingLeft(bool moving)
{
	m_movingLeft = moving;
}

void Player::movingRight(bool moving)
{
	m_movingRight = moving;
}