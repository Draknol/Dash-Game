#include "Level.hpp"

namespace engine
{

Level::Level() {}

Level::Level(const std::string &fileName) { load(fileName); }

void Level::clear()
{
	m_name = "";
	m_platforms.clear();
	m_decorations.clear();
	m_doors.clear();
	m_spawn = { 0.0F, 0.0F };
}

void Level::load(std::string fileName)
{
	clear();
	m_name = fileName;

	std::fstream file;
	file.open("res/Levels/" + m_name + ".map");

	file >> m_spawn.x >> m_spawn.y;

	std::string type;
	while (file >> type)
	{
		switch (type[0])
		{
		case '/':
		case '#':
			std::getline(file, type);
			break;
		case 'p':
			m_platforms.push_back(Block());
			file >> m_platforms.back();
			break;
		case 'd':
			m_decorations.push_back(Block());
			file >> m_decorations.back();
			break;
		case 'D':
			m_doors.push_back(Door());
			file >> m_doors.back();
			break;
		default:
			break;
		}
	}
}

void Level::updateAnimations(float deltaTime)
{
	m_platforms.updateAnimations(deltaTime);
	m_decorations.updateAnimations(deltaTime);
	m_doors.updateAnimations(deltaTime);
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_platforms, states);
	target.draw(m_decorations, states);
	target.draw(m_doors, states);
}

} // namespace engine