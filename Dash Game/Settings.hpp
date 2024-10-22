#pragma once

#include <SFML/System/Vector2.hpp>
#include <fstream>

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
    static Settings& getInstance();

    // enforce singleton
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    /// <summary>
    /// Load settings from file
    /// </summary>
    /// <param name="fileName">name of .sav file (without .sav)</param>
    void load(const std::string& fileName);

    void save(const std::string& fileName);

    void setWindowSize(const sf::Vector2u& windowSize);

    const sf::Vector2u& getWindowSize() const;

    void setWindowPosition(const sf::Vector2i& windowPosition);

    const sf::Vector2i& getWindowPosition() const;

    void setFullscreen(bool fullscreen);

    bool getFullscreen() const;

    void setCurrentLevel(const std::string& currentLevel);

    const std::string& getCurrentLevel() const;

private:

    Settings();

    static Settings instance;

    sf::Vector2u windowSize = { 800U, 800U };
    sf::Vector2i windowPosition = { 0U, 0U };
    bool isFullscreen = false;
    std::string currentLevel = "Level1";
};
