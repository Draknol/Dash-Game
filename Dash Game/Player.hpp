#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/System/Vector2.hpp>

#include "Level.hpp"

class Player : public sf::Sprite
{
public:

	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="position">Players spawn position</param>
	Player(Level& level, sf::Vector2f position);

	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="x">x spawn position</param>
	/// <param name="y">y spawn position</param>
	Player(Level& level, int x, int y);

	/// <summary>
	/// Updates the player
	/// </summary>
	/// <param name="deltaTime">deltaTime</param>
	void update(float deltaTime);

	/// <summary>
	/// Set if the player is moving left
	/// </summary>
	/// <param name="moving">is the player moving left</param>
	void movingLeft(bool moving);

	/// <summary>
	/// Set if the player is moving right
	/// </summary>
	/// <param name="moving">is the player moving right</param>
	void movingRight(bool moving);

	/// <summary>
	/// Set if the player is dashing
	/// </summary>
	/// <param name="dashing"></param>
	void dashing(bool dashing);

private:

	/// <summary>
	/// Move on x axis
	/// </summary>
	void walk();

	/// <summary>
	/// Dash on x axis
	/// </summary>
	void dash();

	/// <summary>
	/// Fall on y axis
	/// </summary>
	void gravity();

	/// <summary>
	/// Moves player to a valid location
	/// </summary>
	void tryMove();

	// Attributes
	float m_deltaTime = 0;
	Level& m_level;
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Vector2f m_velocity = sf::Vector2f(0.0F, 0.0F);

	// Running
	float m_speed = 900.0F;
	bool m_movingLeft = false;
	bool m_movingRight = false;

	// Gravity
	float m_gravityAcceleration = 5000.0F;
	float m_drag = 0.01F;

	// Dashing
	float m_dashSpeed = 6000.0F;
	float m_dashDuration = 0.1F;
	float m_dashCooldown = 0.0F;
	bool m_dashing = false;

};