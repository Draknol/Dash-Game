
#include "Settings.hpp"

Settings Settings::instance;

Settings& Settings::getInstance()
{
    return instance;
}

Settings::Settings()
{
}

void Settings::load(const std::string& fileName)
{
    // Open File
    std::fstream file;
    file.open("Saves/" + fileName + ".sav");

    char name;

    // Read in Settings
    while (file >> name) {
        switch (name) {
        case 'h': // window Height
            file >> windowSize.y;
            break;
        case 'w': // window Width
            file >> windowSize.x;
            break;
        case 'f': // Fullscreen
            file >> isFullscreen;
            break;
        case 'l': // Current Level
            file >> currentLevel;
            break; // Ensure there's a break
        default:
            break;
        }
    }

    // Close File
    file.close();
}

void Settings::save(const std::string& fileName)
{
    // Open File
    std::fstream file;
    file.open("Saves/" + fileName + ".sav");

    file << "h" << windowSize.x
        << "w" << windowSize.y
        << "f" << isFullscreen
        << "l" << currentLevel;

    // Close File
    file.close();
}

void Settings::setWindowSize(const sf::Vector2u& windowSize)
{
    this->windowSize = windowSize;
}

const sf::Vector2u& Settings::getWindowSize() const
{
    return windowSize;
}

void Settings::setWindowPosition(const sf::Vector2i& windowPosition)
{
    this->windowPosition = windowPosition;
}

const sf::Vector2i& Settings::getWindowPosition() const
{
    return windowPosition;
}

void Settings::setFullscreen(bool isFullscreen)
{
    this->isFullscreen = isFullscreen;
}

bool Settings::getFullscreen() const
{
    return isFullscreen;
}

void Settings::setCurrentLevel(const std::string& currentLevel)
{
    this->currentLevel = currentLevel;
}

const std::string& Settings::getCurrentLevel() const
{
    return currentLevel;
}
