#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Block.hpp"

/// <summary>
/// Updatable progress bar
/// make sure window view isn't set to camera when drawing
/// </summary>
class ProgressBar : public Block
{
public:

	/// <param name="position">Position of top left</param>
	/// <param name="value">Progress value (uses reference to update)</param>
	/// <param name="maxValue">Max value (uses reference to update)</param>
	ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color barColor, sf::Color backgroundColor, const int& value, const int& maxValue);

	/// <summary>
	/// Update bar to match new value
	/// </summary>
	void update();

protected:

	using Block::vertices;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	const int& value;
	const int& maxValue;

	Block progress;
};