
#include "SFML/Graphics/RenderTarget.hpp"

#include "Text.hpp"
#include "Block.hpp"

/// <summary>
/// Text with a background that stores a function as a string
/// </summary>
class Button : public sf::Drawable {
public:

	/// <summary>
	/// Constructor for Button
	/// </summary>
	/// <param name="text">Text to display</param>
	/// <param name="font">Font to use</param>
	/// <param name="characterSize">Character size</param>
	/// <param name="position">Position of the center of the top</param>
	/// <param name="textColor">Color of the font</param>
	/// <param name="backgroundColor">Color of the background</param>
	/// <param name="pressedColor">Color of the background when pressed</param>
	/// <param name="function">String identifier for function to run</param>
	Button(const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position, const sf::Color& textColor, const sf::Color& backgroundColor, const sf::Color& pressedColor, const std::string& function);
	
	/// <summary>
	/// Gets string identifier for function
	/// </summary>
	/// <returns>String identifier for function</returns>
	std::string getFunction();

	/// <summary>
	/// Change color to be the pressed color
	/// </summary>
	void setPressedColor();

	/// <summary>
	/// Change color to be the unpressed color
	/// </summary>
	void setReleasedColor();

	/// <summary>
	/// Gets top left corner position
	/// </summary>
	/// <returns>Top left corner position</returns>
	sf::Vector2f getTopLeft();

	/// <summary>
	/// Gets bottom right corner position
	/// </summary>
	/// <returns>Bottom right corner position</returns>
	sf::Vector2f getBottomRight();

protected:

	/// <summary>
	/// Draw button to target
	/// </summary>
	/// <param name="target">Target to draw to</param>
	/// <param name="states">States to use</param>
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(m_background, states);
		target.draw(m_text, states);
	}

private:

	/// <summary>
	/// Change color of background
	/// </summary>
	/// <param name="color">Color to change to</param>
	void setBackgroundColor(const sf::Color& color);

	std::string m_function;
	sf::Color m_pressedColor;
	sf::Color m_releasedColor;
	Block m_background;
	Text m_text;
};