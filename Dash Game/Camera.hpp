#pragma once

#include <SFML/Graphics/View.hpp>

/// <summary>
/// camera class with smooth movement and resize support
/// </summary>
class Camera : public sf::View
{
public:

	Camera(const sf::Vector2f& position, const sf::Vector2u& size, float speed = 10);

	void moveTowards(const sf::Vector2f& position, float deltaTime);

	/// <summary>
	/// Resizes view to fit window
	/// </summary>
	void resize(const sf::Vector2u& windowSize);

private:

	const float speed;
	
};