
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Camera.hpp"

int main()
{

	// Create Window
	sf::RenderWindow window(sf::VideoMode(1920U, 1080U), "Dash Game");

	// Create Player
	Player player(960, 960);

	// Create Camera
	Camera camera(player.getPosition(), sf::Vector2f(1920.0F, 1080.0F), 10.0F);

	// Create Clock
	sf::Clock clock;

	/* Game Loop */
	while (window.isOpen())
	{
		// Update deltaTime
		float deltaTime = clock.restart().asSeconds();

		// Update Camera
		camera.moveTowards(player.getPosition(), deltaTime);

		// Update View
		window.setView(camera);

		// Handle Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close Event
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				camera.resize(window.getSize());
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