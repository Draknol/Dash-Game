#pragma once

#include "TextureManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>

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
	/// <param name="textureKey">name of texture file ("color" for plain color)</param>
	/// <param name="frameCount">number of frames in animation</param>
	/// <param name="frameRate">rate to update animation</param>
	Block(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const std::string& textureKey, int frameCount = 1, int frameRate = 1);

	friend std::istream& operator>>(std::istream& is, Block& block);

	/// <summary>
	/// Update animation based on time passed
	/// </summary>
	void updateAnimations(float deltaTime);

	float getLeft() const;

	float getRight() const;

	float getTop() const;

	float getBottom() const;

protected:
	
	/// <summary>
	/// Flip texture coodinates
	/// </summary>
	void flipHorizontally();


	sf::Vertex& getVertex(size_t index);

	/// <summary>
	/// Sets textureKey
	/// also updates frameCount automatically
	/// </summary>
	/// <param name="textureKey">name of .png file (without .png)</param>
	void setTextureKey(const std::string& textureKey);

	void setFrameRate(int frameRate);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::VertexArray vertices;
	
	TextureManager* textureManager = &TextureManager::getInstance();
	std::string textureKey = "color";
	int frameCount = 1; // Should only be updated through setTextureKey
	int frameRate = 1;
	float currentFrame = 0;

};