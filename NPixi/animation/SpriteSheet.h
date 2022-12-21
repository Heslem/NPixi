#pragma once

#include "../sfml.h"

class SpriteSheet :
	public sf::Drawable
{
public:
	SpriteSheet(sf::Texture& texture, const sf::IntRect& frameRect, const unsigned short& framesCount, const unsigned short& speed);
	~SpriteSheet();
	SpriteSheet(const SpriteSheet&) = delete;

	void next();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setRect(const sf::Vector2f& position, const sf::Vector2f& size);
	void setSize(const sf::Vector2f& size);
	
private:
	sf::Texture& m_Texture;
	sf::VertexArray m_VertexArray;
	sf::IntRect m_Frame;

	unsigned short ticks = 0;
	unsigned short max_ticks;
	const unsigned short m_FramesCount;
	unsigned short m_CurrentFrame;
};