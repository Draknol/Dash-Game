#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/System/Vector2.hpp>

class Player : public sf::Drawable
{
public:
	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="position">Players spawn position</param>
	Player(const sf::Vector2f &position);

	/// <summary>
	/// Constructor for Player
	/// </summary>
	/// <param name="x">x spawn position</param>
	/// <param name="y">y spawn position</param>
	Player(float x, float y);

	/// <summary>
	/// Sets player position
	/// </summary>
	/// <param name="position">Position to move to</param>
	void setPosition(const sf::Vector2f &position);

	/// <summary>
	/// Sets player position
	/// </summary>
	/// <param name="x">x position to move to</param>
	/// <param name="y">y position to move to</param>
	void setPosition(float x, float y);

	sf::Vector2f getPosition();

private:

	/// <summary>
	/// Overide draw function
	/// </summary>
	/// <param name="target">RenderTarget to draw to</param>
	/// <param name="states">RenderStates to use</param>
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	}

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_position;
};