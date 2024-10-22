#pragma once

#include "Camera.hpp"

class UICamera : public Camera
{
public:

	UICamera(const sf::Vector2u& windowSize);

	void resize(const sf::Vector2u& windowSize);

	float getWidth() const;

};