
#include "Text.hpp"

Text::Text(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor)
	: sf::Text(text, font, (int)(characterSize * 6.0F))
{

	setFillColor(textColor);
	setScale(0.1F, 0.1F);
	setPosition(position);

	// Magic number doing magic things
	characterSize = (int)(characterSize * 4.65F);

	// Large sizes don't render so it is capped at 5 blocks
	if (characterSize > 80 * 4.65F)
	{
		characterSize = (int)(80 * 4.65F);
		setCharacterSize((int)(160 * 4.65F));
	}

	// Center text
	float snapDistance = (std::ceil(getGlobalBounds().height / 16.0F) * 16.0F - getGlobalBounds().height) / 2.0F;
	move(-getGlobalBounds().width / 2, position.y - (getGlobalBounds().top - snapDistance));
}

sf::Vector2f Text::getTopLeft() const
{
	return { getGlobalBounds().left, getGlobalBounds().top };
}

sf::Vector2f Text::getBottomRight() const
{
	return getTopLeft() + sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height);
}