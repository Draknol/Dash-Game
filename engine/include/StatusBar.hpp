#pragma once

#include "PhysicsObject.hpp"

class StatusBar : public sf::Drawable
{
public:

	StatusBar(float hudCameraWidth, const std::string& fullKey, const std::string& emptyKey, int height, const unsigned int& value, unsigned int maxValue, bool ltr = true);

	void resize(float hudCameraWidth);

protected:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	std::vector<PhysicsObject> fulls;
	std::vector<PhysicsObject> empties;
	const unsigned int& value;
	float textureWidth;
	bool ltr;

};