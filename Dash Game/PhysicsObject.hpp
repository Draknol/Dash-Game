#pragma once

#include "BlockManager.hpp"
#include "Door.hpp"

/// <summary>
/// Extends Block
/// has basic movement and collision checking
/// </summary>
class PhysicsObject : public Block
{
public:

	PhysicsObject();

	PhysicsObject(const Block& block);

	virtual void updatePhysics(const BlockManager<Block>& blocks, float deltaTime);

	void move(const sf::Vector2f& offset);

	const sf::Vector2f& getPosition() const;

	void setPosition(const sf::Vector2f& destination);

protected:

	/// <summary>
	/// Moves as close to destination as posible without colliding with blocks
	/// </summary>
	void checkedMove(const BlockManager<Block>& blocks, const sf::Vector2f& destination);

	bool isColliding(const Block& block);

	virtual void onGroundImpact();

	/// <summary>
	/// Applys gravity at half strength for accuracy
	/// half should be the first thing run and half last
	/// </summary>
	void halfGravity(float deltaTime);

	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f velocity = sf::Vector2f(0.0F, 0.0F);

private:

	bool facingRight = true;

	// Gravity
	float gravityAcceleration = 2000.0F;
	float gravityTimeStep = 0.001F;
	float drag = 0.0005F;
	float gravityTimer = 0.0f;

	// Collision
	float collisionBuffer = 1.0F;

};