#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "Camera.hpp"
#include "Level.hpp"

class Player : public sf::Sprite
{
public:

	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="level"></param>
	Player(Level& level, Camera& camera);

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
	/// <param name="dashing">is the player dashing</param>
	void dashing(bool dashing);

	/// <summary>
	/// Set if the Player is Jumping
	/// </summary>
	/// <param name="jumping">is the player jumping</param>
	void jumping(bool jumping);

	/// <summary>
	/// Set if the Player is Interacting
	/// </summary>
	/// <param name="interacting">is the player interacting</param>
	void interacting(bool interacting);

	/// <summary>
	/// Moves Player Back to Spawn if Fallen or Force
	/// </summary>
	/// <param name="force">Forces respawn</param>
	void respawn(bool force = false);

	/// <summary>
	/// Resets Player Position and Velocity
	/// </summary>
	void reset();

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

	// Components
	Camera& m_camera;

	// Attributes
	float m_deltaTime = 0.0F;
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Vector2f m_velocity = sf::Vector2f(0.0F, 0.0F);

	// Walking
	const float m_speed = 340.0F;
	bool m_movingRight = false;
	bool m_movingLeft = false;

	// Dashing
	const float m_dashDuration = 0.1F;
	const float m_dashCooldown = 0.7F;
	const float m_dashSpeed = 4000.0F;
	float m_dashDurationTimer = m_dashDuration;
	float m_dashCooldownTimer = 0.0F;
	bool m_dashing = false;

	// Interact
	bool m_interacting = false;

	// Gravity
	const float m_gravityAcceleration = 2000.0F;
	const float m_gravityTimeStep = 0.001F;
	const float m_drag = 0.0005F;
	float m_gravityTimer = 0.0f;

	// Jumping
	const int m_maxJumps = 2;
	const float m_jumpStrength = 500.0F;
	int m_jumpCounter = m_maxJumps;
	bool m_jumpHolding = false;
	bool m_jumping = false;

	// Collision
	const float m_collisionBuffer = 1.0F;
	Level& m_level;

};