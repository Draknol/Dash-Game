#pragma once

#include "Settings.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace engine
{

/// <summary>
/// Extends sf::RenderWindow
/// </summary>
class Window : public sf::RenderWindow
{
  public:

	Window(
		sf::VideoMode mode,
		const std::string &title,
		sf::State state = sf::State::Windowed,
		const sf::ContextSettings &settings = sf::ContextSettings()
	);

	void toggleFullscreen();

  private:

	common::Settings &m_settings = common::Settings::getInstance();
};

} // namespace engine