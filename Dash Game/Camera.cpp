
#include "Camera.hpp"

Camera::Camera(sf::Vector2f position, sf::Vector2u size, float speed)
	: sf::View(position, sf::Vector2f(1920.0F, 1080.0F)), m_speed(speed)
{
	resize(size);
}

void Camera::moveTowards(sf::Vector2f position, float deltaTime)
{
	setCenter(getCenter() + ((position - getCenter()) * std::min(m_speed * deltaTime, 1.0f)));
}

void Camera::resize(sf::Vector2u windowSize)
{
	setSize(getSize().y * (float)windowSize.x / (float)windowSize.y, getSize().y);
}