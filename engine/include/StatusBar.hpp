#pragma once

#include "PhysicsObject.hpp"

namespace engine
{

class StatusBar : public sf::Drawable
{
  public:

	StatusBar(
		float hudCameraWidth,
		const std::string &fullKey,
		const std::string &emptyKey,
		int height,
		const unsigned int &value,
		unsigned int maxValue,
		bool ltr = true
	);

	void resize(float hudCameraWidth);

  protected:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:

	std::vector<PhysicsObject> m_fulls;
	std::vector<PhysicsObject> m_empties;

	const unsigned int &m_value;

	float m_textureWidth;
	bool m_ltr;
};

} // namespace engine