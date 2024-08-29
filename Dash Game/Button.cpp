
#include "Button.hpp"

Button::Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor, const sf::Color& hoverColor, const std::string& function)
	: m_text(text, font, characterSize, position, textColor), m_releasedColor(backgroundColor), m_pressedColor(hoverColor), m_function(function), m_background({ 0, 0 }, { 0, 0 }, backgroundColor, "color")
{
	// Make border big enough to be a nice size
	sf::Vector2f border;
	border.x = (std::ceil(m_text.getGlobalBounds().width / 16.0F) * 16.0F - m_text.getGlobalBounds().width) / 2.0F;
	border.y = (std::ceil(m_text.getGlobalBounds().height / 16.0F) * 16.0F - m_text.getGlobalBounds().height) / 2.0F;

	// Get corners of the text
	float left = m_text.getGlobalBounds().left;
	float top = m_text.getGlobalBounds().top;
	float width = m_text.getGlobalBounds().width;
	float height = m_text.getGlobalBounds().height;

	// Set corners of the background
	m_background[0].position = { left - border.x, top - border.y };
	m_background[1].position = { left - border.x, top + height + border.y };
	m_background[2].position = { left + width + border.x, top + height + border.y };
	m_background[3].position = { left + width + border.x, top - border.y };
}

std::string Button::getFunction()
{
	return m_function;
}

void Button::setPressedColor()
{
	setBackgroundColor(m_pressedColor);
}

void Button::setReleasedColor()
{
	setBackgroundColor(m_releasedColor);
}

void Button::setBackgroundColor(const sf::Color& color) {
	for (int i = 0; i < 4; i++)
	{
		m_background[i].color = color;
	}
}

sf::Vector2f Button::getTopLeft() {
	return m_background[0].position;
}

sf::Vector2f Button::getBottomRight() {
	return m_background[2].position;
}