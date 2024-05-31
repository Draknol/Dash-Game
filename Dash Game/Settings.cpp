#include "Settings.hpp"

Settings::Settings(const std::string& fileName)
{
	load(fileName);
}

void Settings::load(const std::string& fileName)
{
	// Open File
	std::fstream file;
	file.open("Saves/" + fileName + ".sav");

	char name;

	// Read in Settings
	while (file >> name)
	{
		switch (name)
		{
		// window Height
		case 'h':
			file >> m_windowSize.y;
			break;
		// window Width
		case 'w':
			file >> m_windowSize.x;
			break;
		// Fullscreen
		case 'f':
			file >> m_isFullscreen;
			break;
		case 'l':
			file >> m_currentLevel;
		default:
			break;
		}
	}

	// Close File
	file.close();
}

void Settings::setWindowSize(const sf::Vector2u& windowSize)
{
	m_windowSize = windowSize;
}

const sf::Vector2u& Settings::getWindowSize()
{
	return m_windowSize;
}

void Settings::setWindowPosition(const sf::Vector2i& windowPosition)
{
	m_windowPosition = windowPosition;
}

const sf::Vector2i& Settings::getWindowPosition()
{
	return m_windowPosition;
}

void Settings::setFullscreen(bool fullscreen)
{
	m_isFullscreen = fullscreen;
}

bool Settings::getFullscreen()
{
	return m_isFullscreen;
}

void Settings::setCurrentLevel(const std::string& currentLevel) {
	m_currentLevel = currentLevel;
}

const std::string& Settings::getCurrentLevel() {
	return m_currentLevel;
}