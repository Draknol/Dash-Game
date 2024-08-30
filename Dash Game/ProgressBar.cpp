
#include "ProgressBar.hpp"

ProgressBar::ProgressBar(sf::Vector2f position, sf::Vector2f size, sf::Color barColor, sf::Color backgroundColor, const int& value, const int& maxValue)
	: m_value(value), m_maxValue(maxValue)
{
	m_background = Block(position, size, backgroundColor, "color");
	m_progress = Block(position, size, barColor, "color");
}

void ProgressBar::update()
{
	float start = m_background[0].position.x;
	float end = m_background[1].position.x;
	float length = end - start;
	float percent = (float)m_value / (float)m_maxValue;
	m_progress[1].position.x = start + std::max(length * percent, 0.0F);
	m_progress[2].position.x = start + std::max(length * percent, 0.0F);
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	target.draw(m_progress, states);
}