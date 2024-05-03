
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

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
	Level level;
	Level overlay("Menu");
	Menu currentMenu = MainMenu;

	// Create Player
	Player player(level);

	// Create Camera
	Camera camera(player.getPosition(), window.getSize());
	sf::Vector2f cameraOffset;

	// Create Clock
	sf::Clock clock;
	bool paused = false;

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
				case sf::Keyboard::E:
					player.interacting(false);
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
					case GameMenu:
						player.interacting(true);
						break;
					case MainMenu:
						currentMenu = GameMenu;
						level.load(settings.getCurrentLevel());
						overlay.load("Blank");
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
					case GameMenu:
						currentMenu = PauseMenu;
						paused = true;
						break;
					case PauseMenu:
						currentMenu = GameMenu;
						paused = false;
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

		if (!paused) 
		{
			// Update Player
			player.update(deltaTime);
		}

		// Update Camera
		camera.moveTowards(player.getPosition(), deltaTime);

		// Update View
		window.setView(camera);

		// Clear Window with Sky
		window.clear(sf::Color(60, 60, 255));

		// Draw Everything
		level.draw(window);
		overlay.draw(window);
		window.draw(player);

		// Display Window
		window.display();

	}

	return 0;
}