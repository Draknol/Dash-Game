#pragma once

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>

/// <summary>
/// Basic block with a position, size, color and texture
/// </summary>
class Block : public sf::VertexArray
{
public:
	/// <summary>
	/// Constructor for Block
	/// </summary>
	Block();

	/// <summary>
	/// Constructor for Block
	/// </summary>
	/// <param name="position">Top Left of Block</param>
	/// <param name="size">Width and Height of Block</param>
	/// <param name="color">Color of Block</param>
	/// <param name="texture">Name of Texture File ("null" for no texture)</param>
	/// <param name="frameCount">Number of frames in texture</param>
	Block(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& texture, int frameCount = 1, int frameRate = 1);

	void updateFrame(float deltaTime);

	/// <summary>
	/// Get textures name
	/// </summary>
	/// <returns>Textures name</returns>
	const std::string& getTexture() const;

	/// <summary>
	/// Get number of frames
	/// </summary>
	/// <returns>Number of frames</returns>
	int getFrameCount() const;

	/// <summary>
	/// Get current frame (only updates if called)
	/// </summary>
	/// <returns>Current frame index</returns>
	int getCurrentFrame() const;

private:

	// Texture name
	std::string m_texture;
	int m_frameCount = 1;
	int m_frameRate = 1;
	float m_currentFrame = 0;
};