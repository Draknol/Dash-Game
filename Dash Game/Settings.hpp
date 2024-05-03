#pragma once

#include <SFML/System/Vector2.hpp>

#include <fstream>
#include <string>

class Settings
{
public:

	/// <summary>
	/// Constructor for Settings
	/// </summary>
	/// <param name="fileName">Name of .sav file</param>
	Settings(std::string fileName);

	/// <summary>
	/// Load new Settings
	/// </summary>
	/// <param name="fileName">Name of .sav file</param>
	void load(std::string fileName);

	/// <summary>
	/// Set Window Size (doesn't change file)
	/// </summary>
	/// <param name="windowSize">Size of RenderWindow</param>
	void setWindowSize(sf::Vector2u windowSize);

	/// <summary>
	/// Get Window Size
	/// </summary>
	/// <returns>Size of RenderWindow</returns>
	sf::Vector2u getWindowSize();

	/// <summary>
	/// Set Window Position (doesn't change file)
	/// </summary>
	/// <param name="windowPosition">Position of RenderWindow</param>
	void setWindowPosition(sf::Vector2i windowPosition);

	/// <summary>
	/// Get Window Position
	/// </summary>
	/// <returns>Position of Window</returns>
	sf::Vector2i getWindowPosition();

	/// <summary>
	/// Set is Fullscreen (doesn't change file)
	/// </summary>
	/// <param name="fullscreen">is Window Fullscreen</param>
	void setFullscreen(bool fullscreen);

	/// <summary>
	/// Get is Fullscreen
	/// </summary>
	/// /// <returns>is Window Fullscreen</returns>
	bool getFullscreen();

	/// <summary>
	/// Set the Current Level Save
	/// </summary>
	/// <param name="currentLevel">Current Level Name</param>
	void setCurrentLevel(std::string currentLevel);

	/// <summary>
	/// Get Current Level Name
	/// </summary>
	/// /// <returns>Name of Current Level</returns>
	std::string getCurrentLevel();

private:

	// Settings
	sf::Vector2u m_windowSize = sf::Vector2u(800U, 800U);
	sf::Vector2i m_windowPosition = sf::Vector2i(0U, 0U);
	bool m_isFullscreen = false;
	std::string m_currentLevel = "Level1";

};