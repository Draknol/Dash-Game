#pragma once

#include "Level.hpp"
#include "PhysicsObject.hpp"

namespace engine
{

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
	Player(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &fileName);

	void updatePhysics(const BlockManager<Block> &blocks, float deltaTime) override;

	void setWalkingLeft(bool walking);
	void setWalkingRight(bool walking);
	void stopWalking();
	void setJumping(bool jumping);
	void setDashing(bool setDashing) { m_isDashing = setDashing; }

	const unsigned int &getHealth() const { return m_health; }
	const unsigned int &getMaxHealth() const { return m_maxHealth; }
	const unsigned int &getDashCount() const { return m_dashCounter; }

	void damage(int damage);

	/// <summary>
	/// Checks levels doors for collision
	/// if found the doors level is loaded
	/// </summary>
	/// <returns>amount player moved by (intended for updating Camera)</returns>
	sf::Vector2f interact(Level &level);

  private:

	void tryWalk();

	void tryJump();

	void tryDash(float deltaTime);

	void onGroundImpact() override;

	// Walking
	float m_speed = 270.0F;
	int m_walkDirection = 0;
	bool m_facingRight = true;
	bool m_walkingLeft = false;
	bool m_walkingRight = false;

	// Jumping
	unsigned int m_maxJumps = 2;
	float m_jumpStrength = 500.0F;
	unsigned int m_jumpCounter = m_maxJumps;
	bool m_jumpHolding = false;
	bool m_isJumping = false;

	// Dashing
	unsigned int m_dashCounter = 1U;
	float m_dashDuration = 0.1F;
	float m_dashCooldown = 0.7F;
	float m_dashSpeed = 2000.0F;
	float m_dashDurationTimer = m_dashDuration;
	float m_dashCooldownTimer = 0.0F;
	bool m_isDashing = false;

	// Health
	unsigned int m_maxHealth = 10U;
	unsigned int m_health = m_maxHealth;
};

} // namespace engine