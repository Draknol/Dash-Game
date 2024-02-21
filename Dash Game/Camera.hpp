#pragma once

#include <SFML/Graphics/View.hpp>

#include <SFML/System/Vector2.hpp>

class Camera : public sf::View
{
public:

	/// <summary>
	/// Constructor for Camera
	/// </summary>
	/// <param name="position">Position of camera</param>
	/// <param name="size">Size of view</param>
	/// <param name="speed">Speed of camera</param>
	Camera(sf::Vector2f position, sf::Vector2f size, float speed = 10);

	/// <summary>
	/// Moves the Camera towards a position
	/// </summary>
	/// <param name="position">Position to move towards</param>
	/// <param name="deltaTime">Delta Time</param>
	void moveTowards(sf::Vector2f position, float deltaTime);

	/// <summary>
	/// Resizes view to fit window
	/// </summary>
	/// <param name="windowSize">Size of window</param>
	void resize(sf::Vector2u windowSize);

private:

	const float m_speed;
};