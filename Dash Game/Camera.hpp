#pragma once

#include <SFML/Graphics/View.hpp>

class Camera : public sf::View
{
public:

	/// <summary>
	/// Constructor for Camera
	/// </summary>
	/// <param name="position">Position of camera</param>
	/// <param name="size">Size of view</param>
	/// <param name="speed">Speed of camera</param>
	Camera(const sf::Vector2f& position, const sf::Vector2u& size, float speed = 10);

	/// <summary>
	/// Moves the Camera towards a position
	/// </summary>
	/// <param name="position">Position to move towards</param>
	/// <param name="deltaTime">Delta Time</param>
	void moveTowards(const sf::Vector2f& position, float deltaTime);

	/// <summary>
	/// Resizes view to fit window
	/// </summary>
	/// <param name="windowSize">Size of window</param>
	void resize(const sf::Vector2u& windowSize);

private:

	const float m_speed;

	// Avoids artifacts when camera offset is 0
	const sf::Vector2f m_offset = { 0.0F, 0.001F };
};