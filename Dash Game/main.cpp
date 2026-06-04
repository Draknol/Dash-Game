
#include "StatusBar.hpp"
#include "UICamera.hpp"
#include "Player.hpp"
#include "Window.hpp"
#include "Menu.hpp"

void handleEvents(Window& window, Level& level, Level& overlay, Player& player, Camera& camera, UICamera& hudCamera, StatusBar& healthBar, StatusBar& dashBar, bool& paused, Menu& lastMenu);

int main()
{
	Settings& settings = Settings::getInstance();
	settings.load("Settings");

	sf::VideoMode videomode = (
			settings.getFullscreen()?
			videomode = sf::VideoMode::getFullscreenModes()[0]:
			sf::VideoMode({ settings.getWindowSize().x, settings.getWindowSize().y })
		);

	sf::State state = (
			settings.getFullscreen()?
			sf::State::Fullscreen:
			sf::State::Windowed
		);

	Window window(videomode, "Dash Game", state);

	Level level;
	Level overlay("Menu");
	Menu currentMenu = Menu::MainMenu;

	sf::Color skyBlue = sf::Color(60, 60, 255);

	Player player(level.getSpawn(), { 31, 34 }, "Player");

	Camera camera(player.getPosition(), window.getSize());

	sf::Clock clock;
	bool paused = true;
	
	UICamera hudCamera(window.getSize());
	StatusBar healthBar(hudCamera.getWidth(), "Heart", "EmptyHeart", 4, player.getHealth(), player.getMaxHealth(), true);
	StatusBar dashBar(hudCamera.getWidth(), "DashBoot", "EmptyDashBoot", 16, player.getDashCount(), 3, false);

	/* GAME LOOP */

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		handleEvents(window, level, overlay, player, camera, hudCamera, healthBar, dashBar, paused, currentMenu);

		/* UPDATE */

		if (!paused)
		{
			level.updateAnimations(deltaTime);
			player.updateAnimations(deltaTime);
			player.updatePhysics(level.getPlatforms(), deltaTime);
		}

		camera.moveTowards(player.getPosition(), deltaTime);

		/* DRAW */

		window.clear(skyBlue);

		window.setView(camera);
		window.draw(level);

		window.draw(player);

		if (!paused)
		{
			window.setView(hudCamera);
			window.draw(healthBar);
			window.draw(dashBar);
		}
		else
		{
			window.draw(overlay);
		}

		window.display();
	}

	return 0;
}

void handleEvents(Window& window, Level& level, Level& overlay, Player& player, Camera& camera, UICamera& hudCamera, StatusBar& healthBar, StatusBar& dashBar, bool& paused, Menu& currentMenu)
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		else if (event->is<sf::Event::Resized>()) {
			camera.resize(window.getSize());
			hudCamera.resize(window.getSize());
			healthBar.resize(hudCamera.getWidth());
			dashBar.resize(hudCamera.getWidth());
		}
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			switch (keyPressed->scancode)
			{
				case sf::Keyboard::Scancode::A:
				if (!paused) player.setWalkingLeft(true);
				break;
			case sf::Keyboard::Scancode::D:
				if (!paused) player.setWalkingRight(true);
				break;
			case sf::Keyboard::Scancode::Space:
				player.setJumping(true);
				break;
			case sf::Keyboard::Scancode::LShift:
				player.setDashing(true);
				break;
			case sf::Keyboard::Scancode::E:
				camera.move(player.interact(level));
				break;
			case sf::Keyboard::Scancode::F11:
				window.toggleFullscreen();
				camera.resize(window.getSize());
				hudCamera.resize(window.getSize());
				healthBar.resize(hudCamera.getWidth());
				dashBar.resize(hudCamera.getWidth());
				break;
			case sf::Keyboard::Scancode::L: // TODO for testing only
				player.damage(-1);
				break;
			case sf::Keyboard::Scancode::K: // TODO for testing only
				player.damage(1);
				break;
			case sf::Keyboard::Scancode::Escape:
				switch (currentMenu) {
				case Menu::GameMenu:
					currentMenu = Menu::PauseMenu;
					paused = !paused;
					break;
				case Menu::MainMenu:
					level.load("Level1");
					player.setPosition(level.getSpawn());
					overlay.load("Pause");
					currentMenu = Menu::GameMenu;
					paused = !paused;
					break;
				case Menu::PauseMenu:
					currentMenu = Menu::GameMenu;
					paused = !paused;
					break;
				case Menu::SettingsMenu:
					currentMenu = Menu::PauseMenu;
					overlay.load("Pause");
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
			switch (keyReleased->scancode)
			{
			case sf::Keyboard::Scancode::A:
				if (currentMenu != Menu::GameMenu) player.stopWalking();
				else player.setWalkingLeft(false);
				break;
			case sf::Keyboard::Scancode::D:
				if (currentMenu != Menu::GameMenu) player.stopWalking();
				else player.setWalkingRight(false);
				break;
			case sf::Keyboard::Scancode::Space:
				player.setJumping(false);
				break;
			default:
				break;
			}
		}
	}
}