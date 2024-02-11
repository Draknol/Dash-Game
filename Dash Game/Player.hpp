#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/System/Vector2.hpp>

class Player : public sf::Sprite
{
public:

	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="position">Players spawn position</param>
	Player(sf::Vector2f position);

	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="x">x spawn position</param>
	/// <param name="y">y spawn position</param>
	Player(float x, float y);

private:

	sf::Texture m_texture;
};