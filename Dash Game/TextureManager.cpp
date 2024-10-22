#include "TextureManager.hpp"

TextureManager TextureManager::instance;

TextureManager::TextureManager()
{
    // First (and only) frame for solid color texture
    renderStates["color"] = { sf::RenderStates() };
}

TextureManager::~TextureManager()
{
    for (sf::Texture* texture : textures) delete texture;
}

TextureManager& TextureManager::getInstance()
{
    return instance;
}

void TextureManager::loadKey(const std::string& textureKey, unsigned int frameCount)
{
    // Check texture isn't already loaded
    if (renderStates.count(textureKey) == 0) 
    {
        // Load sprite sheet
        sf::Texture spriteSheet;
        spriteSheet.loadFromFile("Textures/" + textureKey + ".png");

        // Get size of each frame
        int frameWidth = spriteSheet.getSize().x / std::max(frameCount, 1U);
        int frameHeight = spriteSheet.getSize().y;

        renderStates[textureKey] = {};
        for (int i = 0; i < (int)frameCount; i++) {

            sf::Texture* frame = new sf::Texture();
            frame->loadFromImage(spriteSheet.copyToImage(), { i * frameWidth, 0, frameWidth, frameHeight });
            frame->setRepeated(true);

            // Store the unique_ptr in the vector
            textures.emplace_back(frame);

            // Add render state for frame
            renderStates[textureKey].emplace_back(frame);
        }
    }
}

const sf::RenderStates& TextureManager::getRenderStates(const std::string& textureKey, unsigned int frame)
{
    if (textureKey == "color") return renderStates.at("color")[0];

    if (renderStates.count(textureKey) == 0)
    {
        printf("Warning: Failed to access renderStates[%s] in TextureManager\n", textureKey.c_str());
        renderStates[textureKey] = { sf::RenderStates() };
    }
    else if (renderStates.at(textureKey).size() <= frame)
    {
        printf("Warning: Failed to access \"%s\", frame %d in TextureManager\n", textureKey.c_str(), (int)frame);
        renderStates.at(textureKey).resize(frame);
        //renderStates.at(textureKey)[frame] = { sf::RenderStates() };
    }

    return renderStates.at(textureKey)[frame];
}

int TextureManager::getFrameCount(const std::string& textureKey)
{
    if (renderStates.count(textureKey) == 0) return 0;
    return (int)renderStates.at(textureKey).size();
}
