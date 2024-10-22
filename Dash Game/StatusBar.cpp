
#include "StatusBar.hpp"

StatusBar::StatusBar(float hudCameraWidth, const std::string& fullKey, const std::string& emptyKey, int height, const unsigned int& value, unsigned int maxValue, bool ltr)
	: value(value), ltr(ltr)
{
	TextureManager& textureManager = TextureManager::getInstance();
	textureManager.loadKey(fullKey);
	textureManager.loadKey(emptyKey);

	sf::Vector2f textureSize = (sf::Vector2f)textureManager.getRenderStates(fullKey).texture->getSize();
	textureWidth = textureSize.x;

	for (size_t i = maxValue; i > 0; i--)
	{
		fulls.emplace_back(Block(sf::Vector2f(0, textureSize.y / 2.0F + height), textureSize, sf::Color::White, fullKey));
		empties.emplace_back(Block(sf::Vector2f(0, textureSize.y / 2.0F + height), textureSize, sf::Color::White, emptyKey));
	}

	resize(hudCameraWidth);
}

void StatusBar::resize(float hudCameraWidth)
{
	if (ltr)
	{
		for (size_t i = 0; i < empties.size(); i++)
		{
			empties[i].setPosition(sf::Vector2f(hudCameraWidth - ((empties.size() - i) * 1.5F * textureWidth), empties[i].getPosition().y));
			fulls[i].setPosition(sf::Vector2f(hudCameraWidth - ((fulls.size() - i) * 1.5F * textureWidth), fulls[i].getPosition().y));
		}
	}
	else
	{
		for (size_t i = 0; i < empties.size(); i++)
		{
			empties[i].setPosition(sf::Vector2f(hudCameraWidth - ((i + 1) * 1.5F * textureWidth), empties[i].getPosition().y));
			fulls[i].setPosition(sf::Vector2f(hudCameraWidth - ((i + 1) * 1.5F * textureWidth), fulls[i].getPosition().y));
		}
	}
}

void StatusBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned int i = 0; i < empties.size(); i++)
	{
		target.draw(empties[i]);
	}

	for (unsigned int i = 0; i < std::min(value, (unsigned int)fulls.size()); i++)
	{
		target.draw(fulls[i]);
	}
}


