
#include "Player.hpp"

Player::Player(float x, float y)
	: Player(sf::Vector2f(x, y)) {}

Player::Player(sf::Vector2f position)
{
	m_texture.loadFromFile("Textures/Player.png");

	setTexture(m_texture);
	setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y);
	setPosition(position);
}

void Player::update(float deltaTime)
{
	m_velocity.x = m_speed * (m_movingRight - m_movingLeft);
	move(m_velocity * deltaTime);

	dash(deltaTime);
}

void Player::movingLeft(bool moving)
{
	m_movingLeft = moving;
}

void Player::movingRight(bool moving)
{
	m_movingRight = moving;
}

void Player::dashing(bool dashing)
{
	m_dashing = dashing;
}

void Player::dash(float deltaTime)
{
	if (m_movingRight == m_movingLeft)
	{
		m_dashing = false;
	}
	if (m_dashCooldown > 0.0F)
	{
		m_dashCooldown -= deltaTime;
		m_dashing = false;
	}
	else if (m_dashing && m_dashDuration > 0.0F)
	{
		m_velocity.x = m_dashSpeed * (m_movingRight - m_movingLeft);
		move(m_velocity * std::min(deltaTime, 0.1F));
		m_dashDuration -= deltaTime;
		if (m_dashDuration <= 0.0F)
		{
			m_dashDuration = 0.1F;
			m_dashCooldown = 1.0F;
		}
	}
}