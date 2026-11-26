#pragma once

#include "Camera.hpp"

namespace engine
{

class UICamera : public Camera
{
  public:

	UICamera(const sf::Vector2u &windowSize);

	void resize(const sf::Vector2u &windowSize);

	float getWidth() const { return getSize().x; }
};

} // namespace engine