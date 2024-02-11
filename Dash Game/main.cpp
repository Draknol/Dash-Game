
#include <SFML/Graphics.hpp>

int main()
{

	// Create Window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Dash Game", sf::Style::Close);

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

		/* Update Window */
		window.clear();
		window.display();
	}

	return 0;
}