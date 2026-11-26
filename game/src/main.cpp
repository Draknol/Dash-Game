#include "Player.hpp"
#include "StatusBar.hpp"
#include "UICamera.hpp"
#include "Window.hpp"

void handleEvents(
	engine::Window &window,
	engine::Level &level,
	engine::Player &player,
	engine::Camera &camera,
	engine::UICamera &hudCamera,
	engine::StatusBar &healthBar,
	engine::StatusBar &dashBar,
	bool &paused
);

int main()
{
	common::Settings &settings = common::Settings::getInstance();
	settings.load("Settings");

	sf::VideoMode videomode =
		(settings.getFullscreen() ? videomode = sf::VideoMode::getFullscreenModes()[0]
								  : sf::VideoMode({ settings.getWindowSize().x, settings.getWindowSize().y }));

	sf::State state = (settings.getFullscreen() ? sf::State::Fullscreen : sf::State::Windowed);

	engine::Window window(videomode, "Dash Game", state);

	engine::Level level("Level1");

	sf::Color skyBlue = sf::Color(60U, 60U, 255U);

	engine::Player player(level.getSpawn(), { 31.0F, 34.0F }, "Player");

	engine::Camera camera(player.getPosition(), window.getSize());

	sf::Clock clock;
	bool paused = false;

	engine::UICamera hudCamera(window.getSize());
	engine::StatusBar healthBar(
		hudCamera.getWidth(), "Heart", "EmptyHeart", 4, player.getHealth(), player.getMaxHealth(), true
	);
	engine::StatusBar dashBar(hudCamera.getWidth(), "DashBoot", "EmptyDashBoot", 16, player.getDashCount(), 1U, false);

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

void handleEvents(
	engine::Window &window,
	engine::Level &level,
	engine::Player &player,
	engine::Camera &camera,
	engine::UICamera &hudCamera,
	engine::StatusBar &healthBar,
	engine::StatusBar &dashBar,
	bool &paused
)
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		else if (event->is<sf::Event::Resized>())
		{
			camera.resize(window.getSize());
			hudCamera.resize(window.getSize());
			healthBar.resize(hudCamera.getWidth());
			dashBar.resize(hudCamera.getWidth());
		}
		else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->scancode)
			{
			case sf::Keyboard::Scancode::A:
				if (!paused)
					player.setWalkingLeft(true);
				break;
			case sf::Keyboard::Scancode::D:
				if (!paused)
					player.setWalkingRight(true);
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
				paused = !paused;
				break;
			default:
				break;
			}
		}
		else if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			switch (keyReleased->scancode)
			{
			case sf::Keyboard::Scancode::A:
				if (paused)
					player.stopWalking();
				else
					player.setWalkingLeft(false);
				break;
			case sf::Keyboard::Scancode::D:
				if (paused)
					player.stopWalking();
				else
					player.setWalkingRight(false);
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