#include "TextureManager.hpp"

namespace engine
{

TextureManager TextureManager::m_instance;

TextureManager::TextureManager()
{
	// First (and only) frame for solid color texture
	m_renderStates["color"] = { sf::RenderStates() };
}

TextureManager::~TextureManager()
{
	for (sf::Texture *texture : m_textures)
		delete texture;
}

void TextureManager::loadKey(const std::string &textureKey, unsigned int frameCount)
{
	// Check texture isn't already loaded
	if (m_renderStates.count(textureKey) == 0U)
	{
		// Load sprite sheet
		sf::Texture spriteSheet;
		if (!spriteSheet.loadFromFile("res/Textures/" + textureKey + ".png"))
		{
			exit(1);
		}

		// Get size of each frame
		unsigned int frameWidth = spriteSheet.getSize().x / std::max(frameCount, 1U);
		unsigned int frameHeight = spriteSheet.getSize().y;

		const sf::Image spriteImage = spriteSheet.copyToImage();

		m_renderStates[textureKey] = {};
		for (size_t i = 0U; i < frameCount; i++)
		{

			sf::Texture *frame = new sf::Texture();
			if (!frame->loadFromImage(
					spriteImage, false, { { (int)(i * frameWidth), 0 }, { (int)frameWidth, (int)frameHeight } }
				))
			{
				exit(1);
			}
			frame->setRepeated(true);

			// Store the unique_ptr in the vector
			m_textures.emplace_back(frame);

			// Add render state for frame
			m_renderStates[textureKey].emplace_back(frame);
		}
	}
}

const sf::RenderStates &TextureManager::getRenderStates(const std::string &textureKey, unsigned int frame)
{
	if (textureKey == "color")
		return m_renderStates.at("color")[0];

	if (m_renderStates.count(textureKey) == 0)
	{
		printf("Warning: Failed to access renderStates[%s] in TextureManager\n", textureKey.c_str());
		m_renderStates[textureKey] = { sf::RenderStates() };
	}
	else if (m_renderStates.at(textureKey).size() <= frame)
	{
		printf("Warning: Failed to access \"%s\", frame %d in TextureManager\n", textureKey.c_str(), (int)frame);
		m_renderStates.at(textureKey).resize(frame);
	}

	return m_renderStates.at(textureKey)[frame];
}

unsigned int TextureManager::getFrameCount(const std::string &textureKey)
{
	if (m_renderStates.count(textureKey) == 0U)
		return 0U;
	return (unsigned int)m_renderStates.at(textureKey).size();
}

} // namespace engine