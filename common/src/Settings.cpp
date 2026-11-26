#include "Settings.hpp"

#include <fstream>

namespace common
{

Settings Settings::s_instance;

void Settings::load(const std::string &fileName)
{
	// Open File
	std::fstream file;
	file.open("res/Saves/" + fileName + ".sav");

	char name;

	// Read in Settings
	while (file >> name)
	{
		switch (name)
		{
		case 'h': // window Height
			file >> m_windowSize.y;
			break;
		case 'w': // window Width
			file >> m_windowSize.x;
			break;
		case 'f': // Fullscreen
			file >> m_isFullscreen;
			break;
		case 'l': // Current Level
			file >> m_currentLevel;
			break; // Ensure there's a break
		default:
			break;
		}
	}

	// Close File
	file.close();
}

void Settings::save(const std::string &fileName)
{
	// Open File
	std::fstream file;
	file.open("res/Saves/" + fileName + ".sav");

	file << "h" << m_windowSize.x << "w" << m_windowSize.y << "f" << m_isFullscreen << "l" << m_currentLevel;

	// Close File
	file.close();
}

} // namespace common