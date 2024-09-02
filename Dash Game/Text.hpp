#pragma once

#include "SFML/Graphics/Text.hpp"

/// <summary>
/// Drawable text, centred horizontally
/// </summary>
class Text : public sf::Text {
public:

    /// <summary>
    /// Constructor for Text
    /// </summary>
    /// <param name="text">Text to display</param>
    /// <param name="font">Font to use</param>
    /// <param name="characterSize">Character size</param>
    /// <param name="position">Position of the center of the top</param>
    /// <param name="textColor">Color of the font</param>
    Text(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor);

    /// <summary>
    /// Gets top left corner position
    /// </summary>
    /// <returns>Top left corner position</returns>
    sf::Vector2f getTopLeft() const;

    /// <summary>
    /// Gets bottom right corner position
    /// </summary>
    /// <returns>Bottom right corner position</returns>
    sf::Vector2f getBottomRight() const;
};