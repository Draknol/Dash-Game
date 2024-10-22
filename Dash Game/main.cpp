
#include "StatusBar.hpp"
#include "UICamera.hpp"
#include "Player.hpp"
#include "Window.hpp"

void handleEvents(Window& window, Level& level, Player& player, Camera& camera, UICamera& hudCamera, StatusBar& healthBar, StatusBar& dashBar, bool& paused);

int main()
{
	Settings& settings = Settings::getInstance();
	settings.load("Settings");

	sf::VideoMode videomode = (
			settings.getFullscreen()?
			videomode = sf::VideoMode::getFullscreenModes()[0]:
			sf::VideoMode(settings.getWindowSize().x, settings.getWindowSize().y)
		);

	int style = (
			settings.getFullscreen()?
			sf::Style::Fullscreen:
			sf::Style::Default
		);

	Window window(videomode, "Dash Game", style);

	Level level("Level1");

	sf::Color skyBlue = sf::Color(60, 60, 255);

	Player player(level.getSpawn(), { 31, 34 }, "Player");

	Camera camera(player.getPosition(), window.getSize());

	sf::Clock clock;
	bool paused = false;
	
	UICamera hudCamera(window.getSize());
	StatusBar healthBar(hudCamera.getWidth(), "Heart", "EmptyHeart", 4, player.getHealth(), player.getMaxHealth(), true);
	StatusBar dashBar(hudCamera.getWidth(), "DashBoot", "EmptyDashBoot", 16, player.getDashCount(), 1, false);

	/* GAME LOOP */

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		handleEvents(window, level, player, camera, hudCamera, healthBar, dashBar, paused);

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

		window.setView(hudCamera);
		window.draw(healthBar);
		window.draw(dashBar);

		window.display();
	}

	return 0;
}

void handleEvents(Window& window, Level& level, Player& player, Camera& camera, UICamera& hudCamera, StatusBar& healthBar, StatusBar& dashBar, bool& paused)
{
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
			hudCamera.resize(window.getSize());
			healthBar.resize(hudCamera.getWidth());
			dashBar.resize(hudCamera.getWidth());
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				if (!paused) player.setWalkingLeft(true);
				break;
			case sf::Keyboard::D:
				if (!paused) player.setWalkingRight(true);
				break;
			case sf::Keyboard::Space:
				player.setJumping(true);
				break;
			case sf::Keyboard::LShift:
				player.setDashing(true);
				break;
			case sf::Keyboard::E:
				camera.move(player.interact(level));
				break;
			case sf::Keyboard::F11:
				window.toggleFullscreen();
				camera.resize(window.getSize());
				hudCamera.resize(window.getSize());
				healthBar.resize(hudCamera.getWidth());
				dashBar.resize(hudCamera.getWidth());
				break;
			case sf::Keyboard::L: // TODO for testing only
				player.damage(-1);
				break;
			case sf::Keyboard::K: // TODO for testing only
				player.damage(1);
				break;
			case sf::Keyboard::Escape:
				paused = !paused;
				break;
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::A:
				if (paused) player.stopWalking();
				else player.setWalkingLeft(false);
				break;
			case sf::Keyboard::D:
				if (paused) player.stopWalking();
				else player.setWalkingRight(false);
				break;
			case sf::Keyboard::Space:
				player.setJumping(false);
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}