#include "Window.hpp"

Window::Window(sf::VideoMode mode, const std::string& title, sf::State state, const sf::ContextSettings& settings)
	: sf::RenderWindow(mode, title, state, settings)
{
	// Disable KeyRepeat for smoother controls
	setKeyRepeatEnabled(false);
}

void Window::toggleFullscreen()
{
	if (!settings.getFullscreen())
	{
		settings.setWindowSize(getSize());
		settings.setWindowPosition(getPosition());
	}

	sf::VideoMode videoMode = settings.getFullscreen()
		? sf::VideoMode({ settings.getWindowSize().x, settings.getWindowSize().y })
		: sf::VideoMode::getFullscreenModes()[0];

	sf::State windowState = settings.getFullscreen()
		? sf::State::Fullscreen
		: sf::State::Windowed;

	create(videoMode, "Dash Game", windowState);

	setPosition(settings.getWindowPosition());
	settings.setFullscreen(!settings.getFullscreen());
}
