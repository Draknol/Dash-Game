
#include "StatusBar.hpp"

namespace engine
{

StatusBar::StatusBar(
	float hudCameraWidth,
	const std::string &fullKey,
	const std::string &emptyKey,
	int height,
	const unsigned int &value,
	unsigned int maxValue,
	bool ltr
)
	: m_value(value), m_ltr(ltr)
{
	TextureManager &textureManager = TextureManager::getInstance();
	textureManager.loadKey(fullKey);
	textureManager.loadKey(emptyKey);

	sf::Vector2f textureSize = (sf::Vector2f)textureManager.getRenderStates(fullKey).texture->getSize();
	m_textureWidth = textureSize.x;

	for (size_t i = maxValue; i > 0U; i--)
	{
		m_fulls.push_back(PhysicsObject(
			Block(sf::Vector2f(0.0F, textureSize.y / 2.0F + (float)height), textureSize, sf::Color::White, fullKey)
		));
		m_empties.push_back(PhysicsObject(
			Block(sf::Vector2f(0.0F, textureSize.y / 2.0F + (float)height), textureSize, sf::Color::White, emptyKey)
		));
	}

	resize(hudCameraWidth);
}

void StatusBar::resize(float hudCameraWidth)
{
	if (m_ltr)
	{
		for (size_t i = 0U; i < m_empties.size(); i++)
		{
			m_empties[i].setPosition(
				sf::Vector2f(
					hudCameraWidth - ((float)(m_empties.size() - i) * 1.5F * m_textureWidth),
					m_empties[i].getPosition().y
				)
			);
			m_fulls[i].setPosition(
				sf::Vector2f(
					hudCameraWidth - ((float)(m_fulls.size() - i) * 1.5F * m_textureWidth), m_fulls[i].getPosition().y
				)
			);
		}
	}
	else
	{
		for (size_t i = 0U; i < m_empties.size(); i++)
		{
			m_empties[i].setPosition(
				sf::Vector2f(hudCameraWidth - ((float)(i + 1) * 1.5F * m_textureWidth), m_empties[i].getPosition().y)
			);
			m_fulls[i].setPosition(
				sf::Vector2f(hudCameraWidth - ((float)(i + 1) * 1.5F * m_textureWidth), m_fulls[i].getPosition().y)
			);
		}
	}
}

void StatusBar::draw(sf::RenderTarget &target, sf::RenderStates /*states*/) const
{
	for (size_t i = 0U; i < m_empties.size(); i++)
	{
		target.draw(m_empties[i]);
	}

	for (size_t i = 0U; i < std::min((size_t)m_value, m_fulls.size()); i++)
	{
		target.draw(m_fulls[i]);
	}
}

} // namespace engine