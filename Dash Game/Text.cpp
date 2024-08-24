#include "Text.hpp"

Text::Text(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor) 
	: m_text(text, font, characterSize), m_background({0, 0}, {0, 0}, backgroundColor, "color") {
	m_text.setFillColor(textColor);
	m_text.setOrigin({ m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2 });
	m_text.setScale({ 0.1F, 0.1F });
	m_text.setPosition(position);
	sf::Vector2f border = { 0.02F * characterSize, 0.01F * characterSize };

	m_background[0].position = { m_text.getGlobalBounds().left - border.x, m_text.getGlobalBounds().top - border.y };
	m_background[1].position = { m_text.getGlobalBounds().left - border.x, m_text.getGlobalBounds().top + m_text.getGlobalBounds().height + border.y };
	m_background[3].position = { m_text.getGlobalBounds().left + m_text.getGlobalBounds().width + border.x, m_text.getGlobalBounds().top - border.y };
	m_background[2].position = { m_text.getGlobalBounds().left + m_text.getGlobalBounds().width + border.x, m_text.getGlobalBounds().top + m_text.getGlobalBounds().height + border.y };
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