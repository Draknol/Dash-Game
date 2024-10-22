#include "Window.hpp"

Window::Window(sf::VideoMode mode, const std::string& title, int style, const sf::ContextSettings& settings)
	: sf::RenderWindow(mode, title, style, settings)
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
		? sf::VideoMode(settings.getWindowSize().x, settings.getWindowSize().y)
		: sf::VideoMode::getFullscreenModes()[0];

	sf::Uint32 windowStyle = settings.getFullscreen()
		? sf::Style::Default
		: sf::Style::Fullscreen;

	create(videoMode, "Dash Game", windowStyle);

	setPosition(settings.getWindowPosition());
	settings.setFullscreen(!settings.getFullscreen());
}
