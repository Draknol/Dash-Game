#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Block.hpp"

/// <summary>
/// Updatable progress bar
/// </summary>
class ProgressBar : public sf::Drawable
{
public:

	/// <summary>
	/// Progress bar constructor
	/// </summary>
	/// <param name="position">Position of top left</param>
	/// <param name="size">Size of bar</param>
	/// <param name="barColor">Color of bar</param>
	/// <param name="backgroundColor">Color of background</param>
	/// <param name="value">Progress value (uses reference to update)</param>
	/// <param name="maxValue">Max value (uses reference to update)</param>
	ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color barColor, sf::Color backgroundColor, const int& value, const int& maxValue);

	/// <summary>
	/// Update bar to match new value
	/// </summary>
	void update();

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	const int& m_value;
	const int& m_maxValue;

	Block m_background;
	Block m_progress;
};