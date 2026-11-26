#include "Player.hpp"

namespace engine
{

Player::Player() {}

Player::Player(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &fileName)
	: PhysicsObject(Block(position, size, sf::Color::White, fileName + "Idle", 5U, 10U))
{
	TextureManager &textureManager = TextureManager::getInstance();
	textureManager.loadKey("PlayerWalk", 8U);
}

void Player::onGroundImpact() { m_jumpCounter = m_maxJumps; }

void Player::setWalkingLeft(bool walking)
{
	m_walkingLeft = walking;
	if (walking == true)
	{
		if (m_facingRight)
			flipHorizontally();
		m_facingRight = false;
		m_walkDirection = -1;
	}
	else if (m_walkDirection == -1)
	{
		m_walkDirection = (int)m_walkingRight;
		if (m_walkingRight)
		{
			flipHorizontally();
			m_facingRight = true;
		}
	}
}

void Player::setWalkingRight(bool walking)
{
	m_walkingRight = walking;
	if (walking == true)
	{
		if (!m_facingRight)
			flipHorizontally();
		m_facingRight = true;
		m_walkDirection = 1;
	}
	else if (m_walkDirection == 1)
	{
		m_walkDirection = -(int)m_walkingLeft;
		if (m_walkingLeft)
		{
			flipHorizontally();
			m_facingRight = false;
		}
	}
}

void Player::stopWalking()
{
	m_walkDirection = 0;
	m_walkingLeft = false;
	m_walkingRight = false;
}

void Player::updatePhysics(const BlockManager<Block> &fulls, float deltaTime)
{
	halfGravity(deltaTime);

	tryJump();

	tryWalk();

	tryDash(deltaTime);

	halfGravity(deltaTime);

	// 1.5F is sqrt(2) rounded up to be safe
	int loopCount = (unsigned int)(1.5F * std::max(m_velocity.x, m_velocity.y) * deltaTime) + 1U;
	float timeStep = deltaTime / (float)loopCount;

	for (size_t i = 0U; i < loopCount; i++)
	{
		checkedMove(fulls, m_velocity * timeStep);
	}
}

void Player::setJumping(bool jumping)
{
	m_isJumping = jumping;
	m_jumpHolding = jumping;
}

void Player::damage(int damage)
{
	if (damage > (int)m_health)
	{
		m_health = 0U;
	}
	else
	{
		m_health -= damage;
		m_health = std::min(m_health, m_maxHealth);
	}
}

sf::Vector2f Player::interact(Level &level)
{
	for (const Door &door : level.getDoors())
	{
		if (isColliding(door))
		{
			sf::Vector2f oldPosition = m_position;
			setPosition(
				door.getLevelSpawn() + (m_position - sf::Vector2f(door.getLeft(), door.getBottom() - 24.0F))
			); // TODO why 24?
			level.load(door.getLevelName());
			return m_position - oldPosition;
		}
	}

	return { 0.0F, 0.0F };
}

void Player::tryWalk()
{
	if (m_walkDirection == 0)
	{
		if (m_velocity.x != 0.0F)
			setTextureKey("PlayerIdle");
		setFrameRate(10U);
	}
	else
	{
		if (m_velocity.x == 0.0F)
			setTextureKey("PlayerWalk");
		setFrameRate(15U);
	}
	m_velocity.x = m_speed * m_walkDirection;
}

void Player::tryJump()
{
	// Check if Can Jump
	if (m_isJumping && m_jumpCounter > 0U || m_jumpHolding && m_jumpCounter == m_maxJumps)
	{
		// Jump
		move(sf::Vector2f(0.0F, -10.0F));
		m_velocity.y = -m_jumpStrength;

		// Update Counter
		m_jumpCounter--;
		m_isJumping = false;
	}
}

void Player::tryDash(float deltaTime)
{
	m_dashCounter = m_dashCooldownTimer <= 0.0F;

	// Check if Dash is on Cooldown
	if (m_dashCooldownTimer > 0.0F || m_walkDirection == 0)
	{
		m_dashCooldownTimer -= deltaTime;
		m_isDashing = false;
	}
	// If not, Dash
	else if (m_isDashing && m_dashDurationTimer > 0.0F)
	{
		// Dash in Correct Direction
		m_velocity.x = m_dashSpeed * m_walkDirection;
		m_dashDurationTimer -= deltaTime;

		// Reset Timers
		if (m_dashDurationTimer <= 0.0F)
		{
			m_dashDurationTimer = m_dashDuration;
			m_dashCooldownTimer = m_dashCooldown;
		}
	}
}

} // namespace engine