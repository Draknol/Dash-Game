
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Settings.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include "HUD.hpp"

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

	// Create Camera
	Camera camera(level.getSpawn(), window.getSize());
	Camera uiCamera({ 0, 0 }, window.getSize());
	sf::View defaultView = window.getDefaultView();

	// Create Player
	Player player(level, camera);

	// Create HUD
	HUD hud(player, window);

	// Create Clock
	sf::Clock clock;
	bool paused = true;

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
				uiCamera.resize(window.getSize());
				break;
			case sf::Event::MouseButtonReleased:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					std::string function = overlay.checkButtons(window.mapPixelToCoords(sf::Mouse::getPosition(window)), false);
					if (function == "null") break;
					if (function == "close") window.close();
					if (function == "resume")
					{
						currentMenu = GameMenu;
						overlay.load("null");
						paused = false;
						break;
					}
					if (function == "escape")
					{
						currentMenu = MainMenu;
						level.load("null");
						overlay.load("Menu");
						break;
					}
					else
					{
						currentMenu = GameMenu;
						level.load(function);
						overlay.load("null");
						player.reset();
						camera.setCenter(level.getSpawn());
						paused = false;
						break;
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.key.code)
				{
				case sf::Mouse::Left:
					overlay.checkButtons(window.mapPixelToCoords(sf::Mouse::getPosition(window)), true);
					break;
				}
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
					player.interacting(true);
					break;
				case sf::Keyboard::Escape:
					// Exit to Menu
					switch (currentMenu)
					{
					case GameMenu:
						currentMenu = PauseMenu;
						overlay.load("Pause");
						paused = true;
						break;
					case PauseMenu:
						currentMenu = GameMenu;
						overlay.load("null");
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
					uiCamera.resize(window.getSize());
					break;
				default:
					break;
				}
			default:
				break;
			}
		}

		if (!paused) 
		{
			// Update Player
			player.update(deltaTime);

			// Update HUD
			hud.update();

			// Update Animations
			level.updateAnimations(deltaTime);
		}

		// Update Camera
		camera.moveTowards(player.getPosition(), deltaTime);

		// Clear Window with Sky
		window.clear(sf::Color(60, 60, 255));

		// Draw World
		window.setView(camera);
		window.draw(level);
		window.draw(player);

		// Draw HUD
		if (!paused)
		{
			window.setView(defaultView);
			window.draw(hud);
		}

		// Draw Overlay
		window.setView(uiCamera);
		window.draw(overlay);

		// Display Window
		window.display();

	}

	return 0;
}