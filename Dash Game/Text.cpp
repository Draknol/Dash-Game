#include "Text.hpp"

Text::Text(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor)
	: m_text(text, font, characterSize * 2 * 3.0F), m_background({ 0, 0 }, { 0, 0 }, backgroundColor, "color") {

	// THIS CODE IS FRAGILE, DON'T TOUCH IT, IT WILL BREAK

	m_text.setFillColor(textColor);
	m_text.setScale({ 0.1F, 0.1F });

	// Magic number doing magic things
	characterSize *= 4.65;

	// Large sizes don't render so it is capped at 5b
	if (characterSize > 5 * 16 * 4.65F)
	{
		characterSize = 5 * 16 * 4.65F;
		m_text.setCharacterSize(5 * 16 * 4.65F * 2);
	}

	float cellSize = 16.0F;

	// Make border big enough to be a nice size
	float borderWidthX = std::ceil(m_text.getGlobalBounds().width / cellSize) * cellSize - m_text.getGlobalBounds().width;
	float borderWidthY = std::ceil(m_text.getGlobalBounds().height / cellSize) * cellSize - m_text.getGlobalBounds().height;
	sf::Vector2f border = { borderWidthX / 2.0F, borderWidthY / 2.0F };

	// No clue why this is needed but it makes the positioning pixel perfect
	float offset = (characterSize / 16) / 12.0F;
	m_text.setPosition({ position.x - (m_text.getGlobalBounds().width / 2), position.y - offset });

	// Get corners of the text
	float left = m_text.getGlobalBounds().left;
	float top = m_text.getGlobalBounds().top;
	float width = m_text.getGlobalBounds().width;
	float height = m_text.getGlobalBounds().height;

	// Set corners of the background
	m_background[0].position = { left - border.x, top - border.y };
	m_background[1].position = { left - border.x, top + height + border.y };
	m_background[3].position = { left + width + border.x, top - border.y };
	m_background[2].position = { left + width + border.x, top + height + border.y };
}

sf::Vector2f Text::getTopLeft() {
	return m_background[0].position;
}

sf::Vector2f Text::getBottomRight() {
	return m_background[2].position;
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_background);
	target.draw(m_text);
} 

void Text::setBackgroundColor(sf::Color color) {
	for (int i = 0; i < 4; i++)
	{
		m_background[i].color = color;
	}
}