#include "Player.hpp"

Player::Player()
{
}

Player::Player(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& fileName)
	: PhysicsObject(Block(position, size, sf::Color::White, fileName + "Idle", 5, 10))
{
	TextureManager& textureManager = TextureManager::getInstance();
	textureManager.loadKey("PlayerWalk", 8);
}

void Player::onGroundImpact()
{
	jumpCounter = maxJumps;
}

void Player::setWalkingLeft(bool walking)
{
	walkingLeft = walking;
	if (walking == true)
	{
		if (facingRight) flipHorizontally();
		facingRight = false;
		walkDirection = -1;
	}
	else if (walkDirection == -1)
	{
		walkDirection = (int)walkingRight;
		if (walkingRight) {
			flipHorizontally();
			facingRight = true;
		}
	}
}

void Player::setWalkingRight(bool walking)
{
	walkingRight = walking;
	if (walking == true)
	{
		if (!facingRight) flipHorizontally();
		facingRight = true;
		walkDirection = 1;
	}
	else if (walkDirection == 1)
	{
		walkDirection = -(int)walkingLeft;
		if (walkingLeft) {
			flipHorizontally();
			facingRight = false;
		}
	}
}

void Player::stopWalking()
{
	walkDirection = 0;
	walkingLeft = false;
	walkingRight = false;
}

void Player::updatePhysics(const BlockManager<Block>& fulls, float deltaTime)
{
	halfGravity(deltaTime);

	tryJump();

	tryWalk();

	tryDash(deltaTime);

	halfGravity(deltaTime);

	// 1.5F is sqrt(2) rounded up to be safe
	int loopCount = (int)(1.5F * std::max(velocity.x, velocity.y) * deltaTime) + 1;
	float timeStep = deltaTime / (float)loopCount;
	
	for (int i = 0; i < loopCount; i++)
	{
		checkedMove(fulls, velocity * timeStep);
	}
}

void Player::setJumping(bool jumping)
{
	isJumping = jumping;
	jumpHolding = jumping;
}

void Player::setDashing(bool setDashing)
{
	isDashing = setDashing;
}

const unsigned int& Player::getHealth() const
{
	return health;
}

const unsigned int& Player::getMaxHealth() const
{
	return maxHealth;
}

const unsigned int& Player::getDashCount() const
{
	return dashCounter;
}

void Player::damage(int damage)
{
	if (damage > (int)health) {
		health = 0;
	}
	else {
		health -= damage;
		health = std::min(health, maxHealth);
	}
}

sf::Vector2f Player::interact(Level& level)
{
	for (const Door& door : level.getDoors())
	{
		if (isColliding(door))
		{
			sf::Vector2f oldPosition = position;
			setPosition(door.getLevelSpawn() + (position - sf::Vector2f(door.getLeft(), door.getBottom() - 24.0F))); // TODO why 24?
			level.load(door.getLevelName());
			return position - oldPosition;
		}
	}

	return { 0.0F, 0.0F };
}

void Player::tryWalk()
{
	if (walkDirection == 0)
	{
		if (velocity.x != 0) setTextureKey("PlayerIdle");
		setFrameRate(10);
	}
	else
	{
		if (velocity.x == 0) setTextureKey("PlayerWalk");
		setFrameRate(15);
	}
	velocity.x = speed * walkDirection;
}

void Player::tryJump()
{
	// Check if Can Jump
	if (isJumping && jumpCounter > 0 || jumpHolding && jumpCounter == maxJumps)
	{
		// Jump
		move(sf::Vector2f(0, -10));
		velocity.y = -jumpStrength;

		// Update Counter
		jumpCounter--;
		isJumping = false;
	}
}

void Player::tryDash(float deltaTime)
{
	dashCounter = dashCooldownTimer <= 0.0F;

	// Check if Dash is on Cooldown
	if (dashCooldownTimer > 0.0F || walkDirection == 0)
	{
		dashCooldownTimer -= deltaTime;
		isDashing = false;
	}
	// If not, Dash
	else if (isDashing && dashDurationTimer > 0.0F)
	{
		// Dash in Correct Direction
		velocity.x = dashSpeed * walkDirection;
		dashDurationTimer -= deltaTime;

		// Reset Timers
		if (dashDurationTimer <= 0.0F)
		{
			dashDurationTimer = dashDuration;
			dashCooldownTimer = dashCooldown;
		}
	}
}
