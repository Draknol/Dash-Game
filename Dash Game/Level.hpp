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
	Block* getBlocks();
	int getBlockCount();
	sf::Vector2f getSpawn();
	float getKillHeight();
private:
	Block* m_blocks = nullptr;
	sf::Vector2f m_spawn;
	float m_killHeight;
	int m_blockCount = 0;
};