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
	/// <param name="level"></param>
	Player(Level& level);

	/// <summary>
	/// Updates the Player
	/// </summary>
	/// <param name="deltaTime">deltaTime</param>
	void update(float deltaTime);

	/// <summary>
	/// Set if the Player is Moving Left
	/// </summary>
	/// <param name="moving">is the player moving left</param>
	void movingLeft(bool moving);

	/// <summary>
	/// Set if the Player is Moving Right
	/// </summary>
	/// <param name="moving">is the player moving right</param>
	void movingRight(bool moving);

	/// <summary>
	/// Set if the Player is Dashing
	/// </summary>
	/// <param name="dashing"></param>
	void dashing(bool dashing);

	/// <summary>
	/// Set if the Player is Jumping
	/// </summary>
	/// <param name="jumping"></param>
	void jumping(bool jumping);

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
	void halfGravity();

	/// <summary>
	/// Jump on y axis
	/// </summary>
	void jump();

	/// <summary>
	/// Moves Player to a Valid Location
	/// </summary>
	void tryMove();

	/// <summary>
	/// Moves Player Back to Spawn if Fallen
	/// </summary>
	void respawn();

	// Attributes
	float m_deltaTime = 0.0F;
	Level& m_level;
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Vector2f m_velocity = sf::Vector2f(0.0F, 0.0F);

	// Walking
	const float m_speed = 900.0F;
	bool m_movingRight = false;
	bool m_movingLeft = false;

	// Dashing
	const float m_dashDuration = 0.1F;
	const float m_dashCooldown = 0.7F;
	float m_dashSpeed = 6000.0F;
	float m_dashDurationTimer = m_dashDuration;
	float m_dashCooldownTimer = 0.0F;
	bool m_dashing = false;

	// Gravity
	const float m_gravityAcceleration = 7000.0F;
	const float m_gravityTimeStep = 0.001F;
	float m_gravityTimer = 0.0f;
	float m_drag = 0.0005F;

	// Jumping
	const int m_maxJumps = 2;
	float m_jumpStrength = 1500.0F;
	int m_jumpCounter = m_maxJumps;
	bool m_jumpHolding = false;
	bool m_jumping = false;

	// Collision
	const float m_collisionBuffer = 1.0F;

};