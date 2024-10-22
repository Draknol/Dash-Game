#pragma once

#include "Level.hpp"
#include "PhysicsObject.hpp"

/// <summary>
/// Extends PhysicsObject
/// can walk, dash and jump
/// has health and can take damage
/// texture files should have prefix used in constructor
/// and follow the format PrefixType.png
/// where Type is replaced with the animation type
/// Idle or Walk (all are needed)
/// </summary>
class Player : public PhysicsObject
{
public:

	Player();

	/// <param name="fileName">prefix of .png files to use</param>
	Player(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& fileName);

	void updatePhysics(const BlockManager<Block>& blocks, float deltaTime) override;

	void setWalkingLeft(bool walking);
	void setWalkingRight(bool walking);
	void stopWalking();
	void setJumping(bool jumping);
	void setDashing(bool dashing);

	const unsigned int& getHealth() const;
	const unsigned int& getMaxHealth() const;
	const unsigned int& getDashCount() const;

	void damage(int damage);

	/// <summary>
	/// Checks levels doors for collision
	/// if found the doors level is loaded
	/// </summary>
	/// <returns>amount player moved by (intended for updating Camera)</returns>
	sf::Vector2f interact(Level& level);

private:

	void tryWalk();

	void tryJump();

	void tryDash(float deltaTime);

	void onGroundImpact() override;

	// Walking
	float speed = 270.0F;
	int walkDirection = 0;
	bool facingRight = true;
	bool walkingLeft = false;
	bool walkingRight = false;

	// Jumping
	int maxJumps = 2;
	float jumpStrength = 500.0F;
	int jumpCounter = maxJumps;
	bool jumpHolding = false;
	bool isJumping = false;

	// Dashing
	unsigned int dashCounter = 1U;
	float dashDuration = 0.1F;
	float dashCooldown = 0.7F;
	float dashSpeed = 2000.0F;
	float dashDurationTimer = dashDuration;
	float dashCooldownTimer = 0.0F;
	bool isDashing = false;

	// Health
	unsigned int maxHealth = 10;
	unsigned int health = maxHealth;

};