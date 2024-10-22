#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureManager
{
public:

    /// <summary>
    /// Gets singleton instance of texture manager
    /// </summary>
    /// <returns>singleton instance</returns>
    static TextureManager& getInstance();

    // enforce singleton
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    /// <summary>
    /// Loads texture from key
    /// if key is already loaded it won't load it again
    /// </summary>
    void loadKey(const std::string& textureKey, unsigned int frameCount = 1);

    const sf::RenderStates& getRenderStates(const std::string& textureKey, unsigned int frame = 0);

    int getFrameCount(const std::string& textureKey);

private:

    TextureManager();

    ~TextureManager();

    static TextureManager instance;

    std::vector<sf::Texture*> textures;
    std::unordered_map<std::string, std::vector<sf::RenderStates>> renderStates;
};
