
#include "Player.hpp"

Player::Player(Level& level, int x, int y)
	: Player(level, sf::Vector2f((float)x, (float)y)) {}

Player::Player(Level& level, sf::Vector2f position)
	: m_level(level)
{
	// Load Player Texture
	m_texture.loadFromFile("Textures/Player.png");

	// Store Player Size
	m_size = (sf::Vector2f)m_texture.getSize();

	// Update Sprite
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

	jump();

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

void Player::jumping(bool jumping)
{
	m_jumping = jumping;
	m_jumpHolding = jumping;
}

void Player::dash()
{
	// Check if Dash is on Cooldown
	if (m_dashCooldown > 0.0F)
	{
		m_dashCooldown -= m_deltaTime;
		m_dashing = false;
	}
	// If not, Dash
	else if (m_dashing && m_dashDuration > 0.0F)
	{
		m_velocity.x = m_dashSpeed * (m_movingRight - m_movingLeft);
		m_dashDuration -= m_deltaTime;

		// Reset Timers after Dash
		if (m_dashDuration <= 0.0F)
		{
			m_dashDuration = 0.1F;
			m_dashCooldown = 1.0F;
		}
	}
}

void Player::jump()
{
	if (m_jumping && m_jumpCount > 0 || m_jumpHolding && m_jumpCount == 2)
	{
		m_velocity.y = -m_jumpStrength;
		m_jumpCount--;
		m_jumping = false;
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
	// Loop Counters
	int loopCount = (int)(std::max(abs(m_velocity.x), abs(m_velocity.y)) * m_deltaTime * 2.0F) + 1;
	float loopDelta = m_deltaTime / (float)loopCount;
	int blockCount = m_level.getBlockCount();

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

		Block* blocks = m_level.getBlocks();

		// Check Blocks
		for (int i = 0; i < blockCount; i++)
		{
			// Get Block Bounds
			Block& block = blocks[i];
			sf::FloatRect blockBounds = block.getGlobalBounds();

			// Check Collision
			if (blockBounds.intersects(playerBounds))
			{

				// Get Block Edges
				sf::Vector2f blockSize = block.getSize();
				float bTop = blockBounds.top;
				float bBottom = blockBounds.top + blockSize.y;
				float bLeft = blockBounds.left;
				float bRight = blockBounds.left + blockSize.x;

				bool bottomCollided = pBottom - 1.0F < bTop;
				bool TopCollided = pTop + 1.0F > bBottom;
				bool rightCollided = pRight - 1.0F < bLeft;
				bool leftCollided = pLeft + 1.0F > bRight;

				// Down
				if (m_velocity.y > 0.0F && bottomCollided && !rightCollided && !leftCollided)
				{
					updatedPosition.y = bTop;
					m_jumpCount = 2;
					m_velocity.y = 0;
				}
				// Up
				else if (m_velocity.y < 0.0F && TopCollided && !rightCollided && !leftCollided)
				{
					updatedPosition.y = bBottom + m_size.y;
					m_velocity.y = 0;
				}
				// Right
				if (m_velocity.x > 0.0F && rightCollided && !bottomCollided && !TopCollided)
				{
					updatedPosition.x = bLeft - m_size.x / 2.0F;
				}
				// Left
				else if (m_velocity.x < 0.0F && leftCollided && !bottomCollided && !TopCollided)
				{
					updatedPosition.x = bRight + m_size.x / 2.0F;
				}
			}
		}

		setPosition(updatedPosition);
	}
}