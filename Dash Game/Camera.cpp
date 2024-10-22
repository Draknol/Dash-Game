
#include "Camera.hpp"

Camera::Camera(const sf::Vector2f& position, const sf::Vector2u& size, float speed)
	: sf::View(position, sf::Vector2f(640.0F, 360.0F)), speed(speed)
{
	resize(size);
}

void Camera::moveTowards(const sf::Vector2f& position, float deltaTime)
{
	setCenter(getCenter() + ((position - getCenter()) * std::min(speed * deltaTime, 1.0f)));
}

void Camera::resize(const sf::Vector2u& windowSize)
{
	setSize(getSize().y * (float)windowSize.x / (float)windowSize.y, getSize().y);
}