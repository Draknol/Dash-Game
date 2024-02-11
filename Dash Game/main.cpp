
#include <SFML/Graphics.hpp>

#include "Player.hpp"

int main()
{

	// Create Window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dash Game", sf::Style::None);

	// Create Player
	Player player(960, 960);

	/* Game Loop */
	while (window.isOpen())
	{

		/* Handle Events */
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close Event
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Clear Window
		window.clear();

		// Draw Everything
		window.draw(player);

		// Display Window
		window.display();

	}

	return 0;
}