
#include "Player.hpp"

Player::Player(Level& level)
	: m_level(level)
{
	// Load Texture
	m_texture.loadFromFile("Textures/Player.png");

	// Store Size
	m_size = (sf::Vector2f)m_texture.getSize();

	// Update Sprite
	setTexture(m_texture);
	setOrigin((float)m_texture.getSize().x / 2.0F, (float)m_texture.getSize().y);
	respawn(true);
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

	respawn(false);
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

void Player::interacting(bool interacting)
{
	m_interacting = interacting;
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

	// Get Blocks
	const std::vector<Block>& platforms = m_level.getPlatforms();

	// Get Doors
	const std::vector<Door>& doors = m_level.getDoors();

	// Force Break on Map Change
	bool looping = true;

	// Loop for Accuracy
	for (int i = 0; looping && i < loopCount; i++)
	{
		// Get Position to Test
		sf::Vector2f updatedPosition = getPosition() + m_velocity * timeStep;

		// Get Player Bounds
		sf::Vector2f playerTopLeft = updatedPosition - sf::Vector2f(m_size.x / 2.0F, m_size.y);
		sf::Vector2f playerBottomRight = updatedPosition + sf::Vector2f(m_size.x / 2.0F, 0.0F);

		// Loop over Blocks
		for (Block platform : platforms)
		{
			// Get Block Bounds
			sf::Vector2f blockTopLeft = sf::Vector2f(platform[3].position.x, platform[1].position.y);
			sf::Vector2f blockBottomRight = sf::Vector2f(platform[1].position.x, platform[3].position.y);

			// Check for Collision
			if (blockTopLeft.x < playerBottomRight.x &&
				blockBottomRight.x > playerTopLeft.x &&
				blockTopLeft.y < playerBottomRight.y &&
				blockBottomRight.y > playerTopLeft.y)
			{

				// Find Collision Direction(s)
				bool bottomCollided = playerBottomRight.y - m_collisionBuffer < blockTopLeft.y;
				bool TopCollided = playerTopLeft.y + m_collisionBuffer > blockBottomRight.y;
				bool rightCollided = playerBottomRight.x - m_collisionBuffer < blockTopLeft.x;
				bool leftCollided = playerTopLeft.x + m_collisionBuffer > blockBottomRight.x;

				// Check Bottom
				if (m_velocity.y > 0.0F && bottomCollided && !rightCollided && !leftCollided)
				{
					updatedPosition.y = blockTopLeft.y;
					m_velocity.y = 0.0F;
					m_jumpCounter = m_maxJumps;
				}
				// Check Top
				else if (m_velocity.y < 0.0F && TopCollided && !rightCollided && !leftCollided)
				{
					updatedPosition.y = blockBottomRight.y + m_size.y;
					m_velocity.y = 0.0F;
				}
				// Check Right
				if (m_velocity.x > 0.0F && rightCollided && !bottomCollided && !TopCollided)
				{
					updatedPosition.x = blockTopLeft.x - m_size.x / 2.0F;
				}
				// Check Left
				else if (m_velocity.x < 0.0F && leftCollided && !bottomCollided && !TopCollided)
				{
					updatedPosition.x = blockBottomRight.x + m_size.x / 2.0F;
				}
			}
		}

		// Update Possition
		setPosition(updatedPosition);

		// Check for Interactions
		if (m_interacting)
		{
			// Loop over Doors
			for (Door door : doors)
			{
				// Get Block Bounds
				sf::Vector2f blockTopLeft = sf::Vector2f(door[3].position.x, door[1].position.y);
				sf::Vector2f blockBottomRight = sf::Vector2f(door[1].position.x, door[3].position.y);

				// Check for Collision
				if (blockTopLeft.x < playerBottomRight.x &&
					blockBottomRight.x > playerTopLeft.x &&
					blockTopLeft.y < playerBottomRight.y &&
					blockBottomRight.y > playerTopLeft.y)
				{
					// Change Level
					m_level.load(door.getDestination());

					// Move to Other Door + Current Player Offset
					sf::Vector2f offset = getPosition() - door[0].position;
					setPosition(door.getLocation() + offset);

					// Break Collision Loop
					looping = false;

					// Stop Interacting
					m_interacting = false;
					break;
				}
			}
		}
	}
}

void Player::respawn(bool force)
{
	// Move to Spawn if Player has Fallen or if Forced
	if (force || getPosition().y > m_level.getKillHeight()) setPosition(m_level.getSpawn());
}

void Player::reset()
{
	respawn(true);
	m_velocity = sf::Vector2f(0, 0);
}