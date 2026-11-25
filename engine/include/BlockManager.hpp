#pragma once

#include "Block.hpp"

/// <summary>
/// Used for storing and drawing Blocks of the same type
/// Blocks off the screen are culled
/// </summary>
/// <typeparam name="T">type must be derived from Block</typeparam>
template <typename T>
class BlockManager : public sf::Drawable, public std::vector<T>
{
	static_assert(std::is_base_of<Block, T>::value, "T must be a Block or derived from Block");
public:

	void updateAnimations(float deltaTime)
	{
		for (std::size_t i = 0; i < this->size(); i++)
		{
			(*this)[i].updateAnimations(deltaTime);
		}
	}

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// Get target bounds
		sf::Vector2f targetTopLeft = target.mapPixelToCoords(sf::Vector2i(0, 0));
		sf::Vector2f targetBottomRight = target.mapPixelToCoords((sf::Vector2i)target.getSize());

		// Loop over platforms
		for (const T& block : *this)
		{
			// Check if block is on screen
			if (block.getLeft() < targetBottomRight.x &&
				block.getRight() > targetTopLeft.x &&
				block.getTop() < targetBottomRight.y &&
				block.getBottom() > targetTopLeft.y)
			{
				// Draw block if on screen
				target.draw(block);
			}
		}
	}
	
};