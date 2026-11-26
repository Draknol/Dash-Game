#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>

namespace common
{

/// <summary>
/// Save file for game settings
/// </summary>
class Settings
{
  public:

	/// <summary>
	/// Gets singleton instance of settings
	/// </summary>
	/// <returns>singleton instance</returns>
	static Settings &getInstance() { return s_instance; }

	// enforce singleton
	Settings(const Settings &) = delete;
	Settings &operator=(const Settings &) = delete;

	/// <summary>
	/// Load settings from file
	/// </summary>
	/// <param name="fileName">name of .sav file (without .sav)</param>
	void load(const std::string &fileName);

	void save(const std::string &fileName);

	void setWindowSize(const sf::Vector2u &windowSize) { m_windowSize = windowSize; }

	const sf::Vector2u &getWindowSize() const { return m_windowSize; }

	void setWindowPosition(const sf::Vector2i &windowPosition) { m_windowPosition = windowPosition; }

	const sf::Vector2i &getWindowPosition() const { return m_windowPosition; }

	void setFullscreen(bool isFullscreen) { m_isFullscreen = isFullscreen; }

	bool getFullscreen() const { return m_isFullscreen; }

	void setCurrentLevel(const std::string &currentLevel) { m_currentLevel = currentLevel; }

	const std::string &getCurrentLevel() const { return m_currentLevel; }

  private:

	Settings() {}

	static Settings s_instance;

	sf::Vector2u m_windowSize = { 800U, 800U };
	sf::Vector2i m_windowPosition = { 0U, 0U };
	bool m_isFullscreen = false;
	std::string m_currentLevel = "Level1";
};

} // namespace common