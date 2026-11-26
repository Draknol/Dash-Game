#pragma once

#include <SFML/Graphics/View.hpp>

namespace engine
{

/// <summary>
/// camera class with smooth movement and resize support
/// </summary>
class Camera : public sf::View
{
  public:

	Camera(const sf::Vector2f &position, const sf::Vector2u &size, float speed = 10.0F);

	void moveTowards(const sf::Vector2f &position, float deltaTime);

	/// <summary>
	/// Resizes view to fit window
	/// </summary>
	void resize(const sf::Vector2u &windowSize);

  private:

	float m_speed;
};

} // namespace engine