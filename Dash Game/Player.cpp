
#include "Player.hpp"

Player::Player(Level& level, Camera& camera)
	: m_level(level), m_camera(camera)
{
	// Load Texture
	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("Textures/PlayerIdle.png");

	int frameCount = (int)(spriteSheet.getSize().x / m_size.x);

	// Initialise maps
	m_animations.emplace("Idle", std::vector<sf::Texture>());
	m_frameCount.emplace("Idle", frameCount);

	for (int i = 0; i < frameCount; i++) {

		// Create frame
		sf::Texture frame;
		frame.loadFromImage(spriteSheet.copyToImage(), sf::IntRect(i * m_size.x, 0, m_size.x, m_size.y));
		frame.setRepeated(true);

		// Store the texture
		m_animations.at("Idle").push_back(frame);
	}

	spriteSheet.loadFromFile("Textures/PlayerWalk.png");

	frameCount = (int)(spriteSheet.getSize().x / m_size.x);

	// Initialise maps
	m_animations.emplace("Walk", std::vector<sf::Texture>());
	m_frameCount.emplace("Walk", frameCount);

	for (int i = 0; i < frameCount; i++) {

		// Create frame
		sf::Texture frame;
		frame.loadFromImage(spriteSheet.copyToImage(), sf::IntRect(i * m_size.x, 0, m_size.x, m_size.y));
		frame.setRepeated(true);

		// Store the texture
		m_animations.at("Walk").push_back(frame);
	}

	// Update Sprite
	setTexture(m_animations.at("Idle")[0]);
	setOrigin((float)m_size.x / 2.0F, (float)m_size.y);
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

	animate();

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
	m_currentAnimation = (m_velocity.x == 0) ? "Idle" : "Walk";
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
		sf::Vector2f playerTopLeft = updatedPosition - sf::Vector2f(m_size.x / 2.0F, (float)m_size.y);
		sf::Vector2f playerBottomRight = updatedPosition + sf::Vector2f(m_size.x / 2.0F, 0.0F);

		// Loop over Blocks
		for (const Block& platform : platforms)
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
				if (m_velocity.y > 0.0F && bottomCollided)
				{
					updatedPosition.y = blockTopLeft.y;
					m_velocity.y = 0.0F;
					m_jumpCounter = m_maxJumps;
				}
				// Check Top
				else if (m_velocity.y < 0.0F && TopCollided)
				{
					updatedPosition.y = blockBottomRight.y + m_size.y;
					m_velocity.y = 0.0F;
				}
				// Check Right
				if (m_velocity.x > 0.0F && rightCollided)
				{
					updatedPosition.x = blockTopLeft.x - m_size.x / 2.0F;
				}
				// Check Left
				else if (m_velocity.x < 0.0F && leftCollided)
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
					// Remember Offsets
					sf::Vector2f offset = getPosition() - door[0].position;
					sf::Vector2f camera_offset = m_camera.getCenter() - getPosition();
					
					// Change Level
					m_level.load(door.getDestination());

					// Move to Other Door + Current Player Offset
					setPosition(door.getLocation() + offset);

					// Adjust
					m_camera.setCenter(getPosition() + camera_offset);

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

void Player::animate()
{
	// Update current frame
	m_currentFrame += m_deltaTime * (float)m_frameRate;
	m_currentFrame = fmodf(m_currentFrame, (float)m_frameCount.at(m_currentAnimation));

	setTexture(m_animations.at(m_currentAnimation)[(unsigned int)m_currentFrame]);
}

void Player::respawn(bool force)
{
	// Move to Spawn if Player has Fallen or if Forced
	if (force || getPosition().y > m_level.getKillHeight())
	{
		m_health = m_maxHealth;
		setPosition(m_level.getSpawn());
	}
}

void Player::reset()
{
	respawn(true);
	m_velocity = sf::Vector2f(0, 0);
}

const int& Player::getHealth() const
{
	return m_health;
}

const int& Player::getMaxHealth() const
{
	return m_maxHealth;
}