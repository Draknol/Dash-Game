#include "UICamera.hpp"

UICamera::UICamera(const sf::Vector2u& windowSize)
	: Camera(sf::Vector2f(180.0F, 180.0F), sf::Vector2u(800U, 800U))
{
	resize(windowSize);
}

void UICamera::resize(const sf::Vector2u& windowSize)
{
	Camera::resize(windowSize);
	setCenter(getSize() / 2.0F);
}

float UICamera::getWidth() const
{
	return getSize().x;
}
