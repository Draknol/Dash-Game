
#include "Player.hpp"

Player::Player(Level& level, int x, int y)
	: Player(level, sf::Vector2f((float)x, (float)y)) {}

Player::Player(Level& level, sf::Vector2f position)
	: m_level(level)
{
	m_texture.loadFromFile("Textures/Player.png");
	m_size = (sf::Vector2f)m_texture.getSize();

	setTexture(m_texture);
	setOrigin((float)m_texture.getSize().x / 2.0F, (float)m_texture.getSize().y);
	setPosition(position);
}

void Player::update(float deltaTime)
{
	m_deltaTime = deltaTime;

	walk();

	gravity();

	dash();

	tryMove();
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

void Player::dash()
{
	if (m_movingRight == m_movingLeft)
	{
		m_dashing = false;
	}
	if (m_dashCooldown > 0.0F)
	{
		m_dashCooldown -= m_deltaTime;
		m_dashing = false;
	}
	else if (m_dashing && m_dashDuration > 0.0F)
	{
		m_velocity.x = m_dashSpeed * (m_movingRight - m_movingLeft);
		//move(m_velocity * std::min(m_deltaTime, 0.1F));
		m_dashDuration -= m_deltaTime;
		if (m_dashDuration <= 0.0F)
		{
			m_dashDuration = 0.1F;
			m_dashCooldown = 1.0F;
		}
	}
}

void Player::gravity()
{
	m_velocity.y += (m_gravityAcceleration - m_drag * m_velocity.y * m_velocity.y) * m_deltaTime;
}

void Player::walk()
{
	m_velocity.x = m_speed * (m_movingRight - m_movingLeft);
}

void Player::tryMove()
{
	// Collision Checks to do
	int loopCount = std::max(abs((int)m_velocity.x), abs((int)m_velocity.y)) + 1;
	float loopDelta = m_deltaTime / (float)loopCount;

	for (int i = 0; i < loopCount; i++)
	{
		// Get Position to test
		sf::Vector2f updatedPosition = getPosition() + m_velocity * loopDelta;

		// Get Player Bounds
		sf::FloatRect playerBounds = getGlobalBounds();
		float pTop = playerBounds.top;
		float pBottom = playerBounds.top + m_size.y;
		float pLeft = playerBounds.left;
		float pRight = playerBounds.left + m_size.x;

		// Check Blocks
		for (int i = 0; i < m_level.getBlockCount(); i++)
		{
			// Get Block Bounds
			sf::FloatRect blockBounds = m_level.getBlocks()[i].getGlobalBounds();
			sf::Vector2f blockSize = m_level.getBlocks()[i].getSize();
			float bTop = blockBounds.top;
			float bBottom = blockBounds.top + blockSize.y;
			float bLeft = blockBounds.left;
			float bRight = blockBounds.left + blockSize.x;

			// Check Collision
			if (blockBounds.intersects(playerBounds))
			{
				// Down
				if (m_velocity.y > 0 && pBottom - 5 < bTop)
				{
					updatedPosition.y = bTop;
				}
				// Up
				else if (m_velocity.y < 0 && pTop + 5 > bBottom)
				{
					updatedPosition.y = bBottom + m_size.y;
				}
				// Right
				if (m_velocity.x > 0 && pRight - 5 < bLeft)
				{
					updatedPosition.x = bLeft - m_size.x / 2.0F;
				}
				// Left
				else if (m_velocity.x < 0 && pLeft + 5 > bRight)
				{
					updatedPosition.x = bRight + m_size.x / 2.0F;
				}
			}
		}

		setPosition(updatedPosition);
	}
}