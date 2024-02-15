#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <fstream>

#include "Block.hpp"

class Level
{
public:
	Level(std::string fileName);
	void draw(sf::RenderWindow& window);
private:
	Block* m_blocks = nullptr;
	int m_blockCount = 0;
};