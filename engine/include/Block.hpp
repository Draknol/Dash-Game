#pragma once

#include "TextureManager.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace engine
{

/// <summary>
/// Basic block with a position, size, color and texture
/// texture is stored in TextureManager
/// </summary>
class Block : public sf::Drawable
{
  public:

	Block();

	/// <summary>
	/// Constructor for Block
	/// </summary>
	/// <param name="position">top left of Block</param>
	/// <param name="textureKey">name of texture file ("color" for plain
	/// color)</param> <param name="frameCount">number of frames in
	/// animation</param> <param name="frameRate">rate to update
	/// animation</param>
	Block(
		const sf::Vector2f &position,
		const sf::Vector2f &size,
		const sf::Color &color,
		const std::string &textureKey,
		unsigned int frameCount = 1U,
		unsigned int frameRate = 1U
	);

	friend std::istream &operator>>(std::istream &is, Block &block);

	/// <summary>
	/// Update animation based on time passed
	/// </summary>
	void updateAnimations(float deltaTime);

	float getLeft() const { return m_vertices[0].position.x; }

	float getRight() const { return m_vertices[3].position.x; }

	float getTop() const { return m_vertices[0].position.y; }

	float getBottom() const { return m_vertices[3].position.y; }

  protected:

	/// <summary>
	/// Flip texture coodinates
	/// </summary>
	void flipHorizontally();

	sf::Vertex &getVertex(size_t index) { return m_vertices[index]; }

	/// <summary>
	/// Sets textureKey
	/// also updates frameCount automatically
	/// </summary>
	/// <param name="textureKey">name of .png file (without .png)</param>
	void setTextureKey(const std::string &textureKey);

	void setFrameRate(unsigned int frameRate) { m_frameRate = frameRate; }

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:

	sf::VertexArray m_vertices;

	TextureManager *m_textureManager = &TextureManager::getInstance();
	std::string m_textureKey = "color";
	unsigned int m_frameCount = 1U; // Should only be updated through setTextureKey
	unsigned int m_frameRate = 1U;
	float m_currentFrame = 0.0F;
};

} // namespace engine