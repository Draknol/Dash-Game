#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <fstream>

#include "Block.hpp"

class Level
{
public:
	Level(std::string fileName);
	void load(std::string fileName);
	void draw(sf::RenderWindow& window);
	Block* getPlatforms();
	int getPlatformCount();
	sf::Vector2f getSpawn();
	float getKillHeight();
private:
	sf::RenderStates m_markerState;
	sf::Texture m_markerTexture;
	Block* m_platforms = nullptr;
	Block* m_markers = nullptr;
	sf::Vector2f m_spawn;
	float m_killHeight;
	int m_platformCount = 0;
	int m_markerCount = 0;
};