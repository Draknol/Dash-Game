
#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject()
{
}

PhysicsObject::PhysicsObject(const Block& block)
	: Block(block), position((getLeft() + getRight()) / 2.0F, getBottom())
{
	size.x = getRight() - getLeft();
	size.y = getBottom() - getTop();
}

void PhysicsObject::updatePhysics(const BlockManager<Block>& fulls, float deltaTime)
{
}

void PhysicsObject::move(const sf::Vector2f& offset)
{
	position = position + offset;

	for (int i = 0; i < 4; i++)
	{
		getVertex(i).position += offset;
	}
}

const sf::Vector2f& PhysicsObject::getPosition() const
{
	return position;
}

void PhysicsObject::setPosition(const sf::Vector2f& destination)
{
	move(destination - position);
}

void PhysicsObject::checkedMove(const BlockManager<Block>& fulls, const sf::Vector2f& destination)
{
	move(destination);
	sf::Vector2f savePosition = position;

	for (const auto& block : fulls)
	{
		// Check for collision
		if (isColliding(block))
		{
			// Find collision direction(s)
			bool bottomCollided = getBottom() - collisionBuffer < block.getTop();
			bool TopCollided = getTop() + collisionBuffer > block.getBottom();
			bool rightCollided = getRight() - collisionBuffer < block.getLeft();
			bool leftCollided = getLeft() + collisionBuffer > block.getRight();

			// Check bottom
			if (velocity.y > 0.0F && bottomCollided)
			{
				savePosition.y = block.getTop();
				velocity.y = 0.0F;
				onGroundImpact();
			}
			// Check top
			else if (velocity.y < 0.0F && TopCollided)
			{
				savePosition.y = block.getBottom() + size.y;
				velocity.y = 0.0F;
			}
			// Check right
			if (velocity.x > 0.0F && rightCollided)
			{
				savePosition.x = block.getLeft() - (size.x / 2.0F);
			}
			// Check left
			else if (velocity.x < 0.0F && leftCollided)
			{
				savePosition.x = block.getRight() + (size.x / 2.0F);
			}
		}
	}

	setPosition(savePosition);
}

bool PhysicsObject::isColliding(const Block& block)
{
	return block.getLeft() < getRight() &&
		   block.getRight() > getLeft() &&
		   block.getTop() < getBottom() &&
		   block.getBottom() > getTop();
}

void PhysicsObject::onGroundImpact()
{
}

void PhysicsObject::halfGravity(float deltaTime)
{
	// Update timer with half deltaTime
	gravityTimer += deltaTime / 2.0F;

	float i = 0;

	// Loop for accuracy
	while (gravityTimer >= gravityTimeStep)
	{
		// Apply gravity with drag
		velocity.y += (gravityAcceleration - drag * velocity.y * velocity.y) * gravityTimeStep;

		// Update timer with timeStep
		gravityTimer -= gravityTimeStep;
	}
}
