
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Camera.hpp"
#include "Level.hpp"

int main()
{

	// Create Window
	sf::RenderWindow window(sf::VideoMode(1920U, 1080U), "Dash Game");
	sf::Vector2u windowSize;
	sf::Vector2i windowPosition;
	bool isFullscreen = false;

	// Disable KeyRepeat
	window.setKeyRepeatEnabled(false);

	// Create Level
	Level level("level1");

	// Create Player
	Player player(level);

	// Create Camera
	Camera camera(player.getPosition(), sf::Vector2f(1920.0F, 1080.0F));

	// Create Clock
	sf::Clock clock;

	/* Game Loop */
	while (window.isOpen())
	{

		// Update deltaTime
		float deltaTime = clock.restart().asSeconds();

		// Handle Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				camera.resize(window.getSize());
				break;
			case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::A:
						player.movingLeft(false);
						break;
					case sf::Keyboard::D:
						player.movingRight(false);
						break;
					case sf::Keyboard::Space:
						player.jumping(false);
						break;
					default:
						break;
					}
					break;
				default:
					break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::A:
					player.movingLeft(true);
					break;
				case sf::Keyboard::D:
					player.movingRight(true);
					break;
				case sf::Keyboard::LShift:
					player.dashing(true);
					break;
				case sf::Keyboard::Space:
					player.jumping(true);
					break;
				case sf::Keyboard::F5:
					level.load("level1");
					break;
				case sf::Keyboard::F11:
					if (isFullscreen)
					{
						window.create(sf::VideoMode(windowSize.x, windowSize.y), "Dash Game");
						window.setPosition(windowPosition);
					}
					else
					{
						windowSize = window.getSize();
						windowPosition = window.getPosition();
						window.create(sf::VideoMode::getFullscreenModes()[0], "Dash Game", sf::Style::Fullscreen);
					}
					isFullscreen = !isFullscreen;
					camera.resize(window.getSize());
					break;
				default:
					break;
				}
			}
		}

		// Update Player
		player.update(deltaTime);

		// Update Camera
		camera.moveTowards(player.getPosition(), deltaTime);

		// Update View
		window.setView(camera);

		// Clear Window
		window.clear();

		// Draw Everything
		level.draw(window);
		window.draw(player);

		// Display Window
		window.display();

	}

	return 0;
}