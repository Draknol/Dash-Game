#include "Button.hpp"

Button::Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor, const sf::Color& hoverColor, const std::string& function)
	: Text(text, font, characterSize, position, textColor, backgroundColor), m_pressedColor(hoverColor), m_function(function)
{
	
}

std::string Button::getFunction()
{
	return m_function;
}

void Button::colorPressed()
{
	setBackgroundColor(m_pressedColor);
}