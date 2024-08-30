
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include <vector>

#include "ScreenAlignment.hpp"
#include "ProgressBar.hpp"
#include "Player.hpp"

/// <summary>
/// HUD for showing player info
/// </summary>
class HUD : public sf::Drawable
{
public:

	/// <summary>
	/// Constructor for HUD
	/// </summary>
	/// <param name="player">Player reference</param>
	/// <param name="window">Window reference (for scale)</param>
	HUD(const Player& player, const sf::RenderWindow& window);

	/// <summary>
	/// Update scale and progress bar values
	/// </summary>
	void update();

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	const Player& m_player;
	const sf::RenderWindow& m_window;
	sf::Vector2f m_percent;

	std::vector<ProgressBar> m_bars;

};