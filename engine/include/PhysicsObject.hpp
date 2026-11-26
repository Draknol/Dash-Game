#pragma once

#include "BlockManager.hpp"
#include "Door.hpp"

namespace engine
{

/// <summary>
/// Extends Block
/// has basic movement and collision checking
/// </summary>
class PhysicsObject : public Block
{
  public:

	PhysicsObject();

	PhysicsObject(const Block &block);

	virtual void updatePhysics(const BlockManager<Block> &blocks, float deltaTime);

	void move(const sf::Vector2f &offset);

	const sf::Vector2f &getPosition() const { return m_position; }

	void setPosition(const sf::Vector2f &destination) { move(destination - m_position); }

  protected:

	/// <summary>
	/// Moves as close to destination as posible without colliding with blocks
	/// </summary>
	void checkedMove(const BlockManager<Block> &blocks, const sf::Vector2f &destination);

	bool isColliding(const Block &block);

	virtual void onGroundImpact();

	/// <summary>
	/// Applys gravity at half strength for accuracy
	/// half should be the first thing run and half last
	/// </summary>
	void halfGravity(float deltaTime);

	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity = sf::Vector2f(0.0F, 0.0F);

  private:

	bool m_facingRight = true;

	// Gravity
	float m_gravityAcceleration = 2000.0F;
	float m_gravityTimeStep = 0.001F;
	float m_drag = 0.0005F;
	float m_gravityTimer = 0.0F;
};

} // namespace engine