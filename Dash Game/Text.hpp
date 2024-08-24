#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Block.hpp"

class Text : public sf::Drawable {
public:
    Text(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor);

    sf::Vector2f getTopLeft();
    sf::Vector2f getBottomRight();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Block m_background;
    sf::Text m_text;
};