#pragma once

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>

namespace engine
{

class TextureManager
{
  public:

	/// <summary>
	/// Gets singleton instance of texture manager
	/// </summary>
	/// <returns>singleton instance</returns>
	static TextureManager &getInstance() { return m_instance; }

	// enforce singleton
	TextureManager(const TextureManager &) = delete;
	TextureManager &operator=(const TextureManager &) = delete;

	/// <summary>
	/// Loads texture from key
	/// if key is already loaded it won't load it again
	/// </summary>
	void loadKey(const std::string &textureKey, unsigned int frameCount = 1U);

	const sf::RenderStates &getRenderStates(const std::string &textureKey, unsigned int frame = 0U);

	unsigned int getFrameCount(const std::string &textureKey);

  private:

	TextureManager();

	~TextureManager();

	static TextureManager m_instance;
	std::vector<sf::Texture *> m_textures;
	std::unordered_map<std::string, std::vector<sf::RenderStates>> m_renderStates;
};

} // namespace engine