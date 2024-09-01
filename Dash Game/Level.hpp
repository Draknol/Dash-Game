#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>

#include <unordered_map>
#include <fstream>
#include <vector>

#include "Button.hpp"
#include "Block.hpp"
#include "Door.hpp"


/// <summary>
/// Level with blocks, loaded from a .map file
/// </summary>
class Level : public sf::Drawable
{
public:

	/// <summary>
	/// Constructor for Level
	/// </summary>
	/// <param name="fileName">Name of .map file</param>
	Level(const std::string& fileName);

	/// <summary>
	/// Constructor for Level
	/// </summary>
	Level();

	/// <summary>
	/// Unload Map/Load Blank Map (not textures)
	/// </summary>
	void erase();

	/// <summary>
	/// Load new Map
	/// </summary>
	/// <param name="fileName">Name of .map file</param>
	/// <param name="origin">Where should 0, 0 be</param>
	void load(const std::string& fileName);

	/// <summary>
	/// Draw Blocks to Window
	/// </summary>
	/// <param name="window">Window to draw to</param>
	void draw(sf::RenderWindow& window);

	/// <summary>
	/// Gets Platforms Vector
	/// </summary>
	/// <returns>Vector of Platforms</returns>
	const std::vector<Block>& getPlatforms();

	/// <summary>
	/// Gets Doors Vector
	/// </summary>
	/// <returns>Gets Vector of Doors</returns>
	const std::vector<Door>& getDoors();

	/// <summary>
	/// Gets Spawn Point for the Current Map
	/// </summary>
	/// <returns>Spawn Point for the Current Map</returns>
	const sf::Vector2f& getSpawn();

	/// <summary>
	/// Gets Kill Height for the Current Map
	/// </summary>
	/// <returns>Kill Height for the Current Map</returns>
	float getKillHeight();

	/// <summary>
	/// Gets Name of the Current Map
	/// </summary>
	/// <returns></returns>
	const std::string& getName();

	/// <summary>
	/// Check if any buttons are under the mouse
	/// </summary>
	/// <param name="mousePosition">Position of the mouse</param>
	/// <param name="press">Is the button being pressed or released</param>
	/// <returns>Function to happen when pressed of button under mouse ("null" if released or no button)</returns>
	std::string checkButtons(sf::Vector2f mousePosition, bool press);

	/// <summary>
	/// Tells animated textures that time has passed
	/// </summary>
	void updateAnimations(float deltaTime);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	/// <summary>
	/// Gets a sf::Color from hex
	/// </summary>
	static sf::Color fromHex(uint32_t hex);

	// Level
	std::string m_name;

	// Blocks
	std::vector<Block> m_platforms;
	std::vector<Block> m_decorations;
	std::vector<Door> m_doors;
	std::vector<Text> m_texts;
	std::vector<Button> m_buttons;

	// Player
	sf::Vector2f m_spawn;
	float m_killHeight;

	// Textures
	std::unordered_map<std::string, sf::RenderStates> m_renderStates;
	std::vector<sf::Texture*> m_textures;

	// Fonts
	std::unordered_map<std::string, sf::Font*> m_fonts;
};