#include "PhysicsObject.hpp"

namespace engine
{

PhysicsObject::PhysicsObject() {}

PhysicsObject::PhysicsObject(const Block &block)
	: Block(block), m_position((getLeft() + getRight()) / 2.0F, getBottom())
{
	m_size.x = getRight() - getLeft();
	m_size.y = getBottom() - getTop();
}

void PhysicsObject::updatePhysics(const BlockManager<Block> & /*blocks*/, float /*deltaTime*/) {}

void PhysicsObject::move(const sf::Vector2f &offset)
{
	m_position = m_position + offset;

	for (size_t i = 0U; i < 4U; i++)
	{
		getVertex(i).position += offset;
	}
}

void PhysicsObject::checkedMove(const BlockManager<Block> &fulls, const sf::Vector2f &destination)
{
	move(destination);
	sf::Vector2f savePosition = m_position;

	for (const auto &block : fulls)
	{
		// Check for collision
		if (isColliding(block))
		{
			// Find collision direction(s)
			float bottomCollided = block.getTop() - getBottom();
			float TopCollided = getTop() - block.getBottom();
			float rightCollided = block.getLeft() - getRight();
			float leftCollided = getLeft() - block.getRight();
			float maxCollided = std::max(std::max(bottomCollided, TopCollided), std::max(rightCollided, leftCollided));

			// Check bottom
			if (m_velocity.y > 0.0F && bottomCollided == maxCollided)
			{
				savePosition.y = block.getTop();
				m_velocity.y = 0.0F;
				onGroundImpact();
			}
			// Check top
			else if (m_velocity.y < 0.0F && TopCollided == maxCollided)
			{
				savePosition.y = block.getBottom() + m_size.y;
				m_velocity.y = 0.0F;
			}
			// Check right
			else if (m_velocity.x > 0.0F && rightCollided == maxCollided)
			{
				savePosition.x = block.getLeft() - (m_size.x / 2.0F);
			}
			// Check left
			else if (m_velocity.x < 0.0F && leftCollided == maxCollided)
			{
				savePosition.x = block.getRight() + (m_size.x / 2.0F);
			}
		}
	}

	setPosition(savePosition);
}

bool PhysicsObject::isColliding(const Block &block)
{
	return block.getLeft() < getRight() && block.getRight() > getLeft() && block.getTop() < getBottom() &&
		   block.getBottom() > getTop();
}

void PhysicsObject::onGroundImpact() {}

void PhysicsObject::halfGravity(float deltaTime)
{
	// Update timer with half deltaTime
	m_gravityTimer += deltaTime / 2.0F;

	float i = 0;

	// Loop for accuracy
	while (m_gravityTimer >= m_gravityTimeStep)
	{
		// Apply gravity with drag
		m_velocity.y += (m_gravityAcceleration - m_drag * m_velocity.y * m_velocity.y) * m_gravityTimeStep;

		// Update timer with timeStep
		m_gravityTimer -= m_gravityTimeStep;
	}
}

} // namespace engine