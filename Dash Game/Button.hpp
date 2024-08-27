#include "Text.hpp"

class Button : public Text {
public:

	Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor, const sf::Color& hoverColor, const std::string& function);
	
	std::string getFunction();

	void colorPressed();

private:

	std::string m_function;
	sf::Color m_pressedColor;
};