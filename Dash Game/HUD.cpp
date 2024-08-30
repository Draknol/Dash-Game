
#include "HUD.hpp"

HUD::HUD(const Player& player, const sf::RenderWindow& window)
	: m_player(player), m_window(window)
{
	update();

	// Add healthbar
	m_bars.emplace_back(sf::Vector2f(78 * m_percent.x, 3 * m_percent.y), sf::Vector2f(20 * m_percent.x, 3 * m_percent.y), sf::Color::Red, sf::Color::Black, player.getHealth(), player.getMaxHealth());
}

void HUD::update()
{
	m_percent = (sf::Vector2f)m_window.getSize() / 100.0F;

	for (ProgressBar& bar : m_bars)
	{
		bar.update();
	}
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const ProgressBar& bar : m_bars)
	{
		target.draw(bar, states);
	}
}