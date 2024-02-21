
#include "Player.hpp"

Player::Player(Level& level, int x, int y)
	: Player(level, sf::Vector2f((float)x, (float)y)) {}

Player::Player(Level& level, sf::Vector2f position)
	: m_level(level)
{
	// Load Texture
	m_texture.loadFromFile("Textures/Player.png");

	// Store Size
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

	halfGravity();

	jump();

	dash();

	halfGravity();

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
	if (m_dashCooldownTimer > 0.0F)
	{
		m_dashCooldownTimer -= m_deltaTime;
		m_dashing = false;
	}
	// If not, Dash
	else if (m_dashing && m_dashDurationTimer > 0.0F)
	{
		// Dash in Correct Direction
		m_velocity.x = m_dashSpeed * (m_movingRight - m_movingLeft);
		m_dashDurationTimer -= m_deltaTime;

		// Reset Timers
		if (m_dashDurationTimer <= 0.0F)
		{
			m_dashDurationTimer = m_dashDuration;
			m_dashCooldownTimer = m_dashCooldown;
		}
	}
}

void Player::jump()
{
	// Check if Can Jump
	if (m_jumping && m_jumpCounter > 0 || m_jumpHolding && m_jumpCounter == m_maxJumps)
	{
		// Jump
		m_velocity.y = -m_jumpStrength;

		// Update Counter
		m_jumpCounter--;
		m_jumping = false;
	}
}

void Player::halfGravity()
{
	// Update Timer with Half deltaTime
	m_gravityTimer += m_deltaTime / 2.0F;

	// Loop for Accuracy
	while (m_gravityTimer >= m_gravityTimeStep)
	{
		// Apply Gravity with Drag
		m_velocity.y += (m_gravityAcceleration - m_drag * m_velocity.y * m_velocity.y) * m_gravityTimeStep;

		// Update Timer with timeStep
		m_gravityTimer -= m_gravityTimeStep;
	}
}

void Player::walk()
{
	// Sets m_velocity in Correct Direction
	m_velocity.x = m_speed * (m_movingRight - m_movingLeft);
}

void Player::tryMove()
{
	// Loop Counters (x2 is precautionary)
	int loopCount = (int)(std::max(abs(m_velocity.x), abs(m_velocity.y)) * m_deltaTime) * 2 + 1;
	float timeStep = m_deltaTime / (float)loopCount;
	int blockCount = m_level.getBlockCount();

	// Loop for Accuracy
	for (int i = 0; i < loopCount; i++)
	{
		// Get Position to test
		sf::Vector2f updatedPosition = getPosition() + m_velocity * timeStep;

		// Get Player Bounds
		sf::FloatRect playerBounds = getGlobalBounds();
		float playerTop = playerBounds.top;
		float playerBottom = playerBounds.top + m_size.y;
		float playerLeft = playerBounds.left;
		float playerRight = playerBounds.left + m_size.x;

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
				float blockTop = blockBounds.top;
				float blockBottom = blockBounds.top + blockSize.y;
				float blockLeft = blockBounds.left;
				float blockRight = blockBounds.left + blockSize.x;

				// Pre-Computed Checks
				bool bottomCollided = playerBottom - m_collisionBuffer < blockTop;
				bool TopCollided = playerTop + m_collisionBuffer > blockBottom;
				bool rightCollided = playerRight - m_collisionBuffer < blockLeft;
				bool leftCollided = playerLeft + m_collisionBuffer > blockRight;

				// Check Bottom
				if (m_velocity.y > 0.0F && bottomCollided && !rightCollided && !leftCollided)
				{
					updatedPosition.y = blockTop;
					m_jumpCounter = m_maxJumps;
					m_velocity.y = 0.0F;
				}
				// Check Top
				else if (m_velocity.y < 0.0F && TopCollided && !rightCollided && !leftCollided)
				{
					updatedPosition.y = blockBottom + m_size.y;
					m_velocity.y = 0.0F;
				}
				// Check Right
				if (m_velocity.x > 0.0F && rightCollided && !bottomCollided && !TopCollided)
				{
					updatedPosition.x = blockLeft - m_size.x / 2.0F;
				}
				// Check Left
				else if (m_velocity.x < 0.0F && leftCollided && !bottomCollided && !TopCollided)
				{
					updatedPosition.x = blockRight + m_size.x / 2.0F;
				}
			}
		}

		setPosition(updatedPosition);
	}
}