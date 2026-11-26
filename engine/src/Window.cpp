#include "Window.hpp"

namespace engine
{

Window::Window(sf::VideoMode mode, const std::string &title, sf::State state, const sf::ContextSettings &settings)
	: sf::RenderWindow(mode, title, state, settings)
{
	// Disable KeyRepeat for smoother controls
	setKeyRepeatEnabled(false);
}

void Window::toggleFullscreen()
{
	if (m_settings.getFullscreen())
	{
		create(sf::VideoMode(m_settings.getWindowSize()), "Dash Game", sf::State::Windowed);
		setPosition(m_settings.getWindowPosition());
	}
	else
	{
		m_settings.setWindowSize(getSize());
		m_settings.setWindowPosition(getPosition());

		create(sf::VideoMode::getFullscreenModes()[0], "Dash Game", sf::State::Fullscreen);
		setPosition(sf::Vector2i(0, 0));
	}

	m_settings.setFullscreen(!m_settings.getFullscreen());
}

} // namespace engine