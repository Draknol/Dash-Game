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

	void update(float deltaTime);

	void movingLeft(bool moving);
	void movingRight(bool moving);

private:

	sf::Texture m_texture;
	sf::Vector2f m_velocity = sf::Vector2f(0.0F, 0.0F);
	float m_speed = 300.0F;
	bool m_movingLeft = false;
	bool m_movingRight = false;
};