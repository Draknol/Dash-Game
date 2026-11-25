#include "Window.hpp"

Window::Window(sf::VideoMode mode, const std::string& title, sf::State state, const sf::ContextSettings& settings)
	: sf::RenderWindow(mode, title, state, settings)
{
	// Disable KeyRepeat for smoother controls
	setKeyRepeatEnabled(false);
}

void Window::toggleFullscreen()
{
	if (settings.getFullscreen())
	{
		create(
			sf::VideoMode(settings.getWindowSize()),
			"Dash Game",
			sf::State::Windowed
		);
		setPosition(settings.getWindowPosition());
	}
	else
	{
		settings.setWindowSize(getSize());
		settings.setWindowPosition(getPosition());

		create(
			sf::VideoMode::getFullscreenModes()[0],
			"Dash Game",
			sf::State::Fullscreen
		);
		setPosition(sf::Vector2i(0, 0));
	}

	settings.setFullscreen(!settings.getFullscreen());
}
