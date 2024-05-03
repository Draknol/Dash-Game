#include "Settings.hpp"

Settings::Settings(std::string fileName)
{
	load(fileName);
}

void Settings::load(std::string fileName)
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

void Settings::setWindowSize(sf::Vector2u windowSize)
{
	m_windowSize = windowSize;
}

sf::Vector2u Settings::getWindowSize()
{
	return m_windowSize;
}

void Settings::setWindowPosition(sf::Vector2i windowPosition)
{
	m_windowPosition = windowPosition;
}

sf::Vector2i Settings::getWindowPosition()
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

void Settings::setCurrentLevel(std::string currentLevel) {
	m_currentLevel = currentLevel;
}

std::string Settings::getCurrentLevel() {
	return m_currentLevel;
}