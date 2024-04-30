
#include <SFML/Graphics.hpp>

#include "Settings.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Level.hpp"
#include "Menu.hpp"

int main()
{

	// Load Settings
	Settings settings("Settings");

	// Create Window
	sf::VideoMode videomode(settings.getFullscreen() ? sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode(settings.getWindowSize().x, settings.getWindowSize().y));
	sf::RenderWindow window(videomode, "Dash Game", settings.getFullscreen() ? sf::Style::Fullscreen : sf::Style::Default);
	
	// Disable KeyRepeat
	window.setKeyRepeatEnabled(false);

	// Create Level
	Level level("Menu");
	Menu currentMenu = MainMenu;
	std::string lastLevel = "Level1"; 

	// Create Player
	Player player(level);

	// Create Camera
	Camera camera(player.getPosition(), window.getSize());
	sf::Vector2f cameraOffset;

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
			switch (event.type)
			{
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
				case sf::Keyboard::E:
					// Start Game
					switch (currentMenu)
					{
					case MainMenu:
						currentMenu = NullMenu;
						level.load(lastLevel);
						player.reset();
						camera.setCenter(level.getSpawn());
						break;
					default:
						break;
					}
					break;
				case sf::Keyboard::Escape:
					// Exit to Menu
					switch (currentMenu)
					{
					case NullMenu:
						lastLevel = level.getName();
						currentMenu = MainMenu;
						level.load("Menu");
						cameraOffset = camera.getCenter() - player.getPosition();
						player.reset();
						camera.setCenter(level.getSpawn() + cameraOffset);
						break;
					case MainMenu:
						window.close();
						break;
					default:
						break;
					}
					break;
				case sf::Keyboard::F5:
					level.load(level.getName());
					break;
				case sf::Keyboard::F11:
					// Toggle Fullscreen
					if (settings.getFullscreen())
					{
						window.create(sf::VideoMode(settings.getWindowSize().x, settings.getWindowSize().y), "Dash Game");
						window.setPosition(settings.getWindowPosition());
					}
					else
					{
						settings.setWindowSize(window.getSize());
						settings.setWindowPosition(window.getPosition());
						window.create(sf::VideoMode::getFullscreenModes()[0], "Dash Game", sf::Style::Fullscreen);
					}
					settings.setFullscreen(!settings.getFullscreen());
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

		// Clear Window with Sky
		window.clear(sf::Color(60, 60, 255));

		// Draw Everything
		level.draw(window);
		window.draw(player);

		// Display Window
		window.display();

	}

	return 0;
}