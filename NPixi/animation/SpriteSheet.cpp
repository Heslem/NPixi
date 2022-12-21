#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(sf::Texture& texture, const sf::IntRect& frameRect, const unsigned short& framesCount, const unsigned short& speed)
	: m_Texture(texture), m_VertexArray(sf::PrimitiveType::Quads, 4), m_FramesCount(framesCount),
	m_CurrentFrame(0), m_Frame(frameRect), max_ticks(speed)
{
	setRect(sf::Vector2f(m_Frame.width * (int)m_CurrentFrame, 0), sf::Vector2f(m_Frame.width, m_Frame.height));
	setSize(sf::Vector2f(frameRect.width, frameRect.height));
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::next()
{
	ticks++;
	if (ticks > max_ticks) {
		m_CurrentFrame++;
		if (m_CurrentFrame > m_FramesCount) {
			m_CurrentFrame = 0;
		}
		setRect(sf::Vector2f(m_Frame.width * (int)m_CurrentFrame, 0), sf::Vector2f(m_Frame.width, m_Frame.height));
		ticks = 0;
	}
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_Texture;
	target.draw(m_VertexArray, states);
}

void SpriteSheet::setRect(const sf::Vector2f& position, const sf::Vector2f& size)
{
	m_VertexArray[0].texCoords = sf::Vector2f(position.x, position.y);
	m_VertexArray[1].texCoords = sf::Vector2f(position.x + size.x, position.y);
	m_VertexArray[2].texCoords = sf::Vector2f(position.x + size.x, position.y + size.y);
	m_VertexArray[3].texCoords = sf::Vector2f(position.x, position.y + size.y);
}

void SpriteSheet::setSize(const sf::Vector2f& size)
{
	m_VertexArray[0].position = sf::Vector2f(0, 0);
	m_VertexArray[1].position = sf::Vector2f(size.x, 0);
	m_VertexArray[2].position = sf::Vector2f(size.x, size.y);
	m_VertexArray[3].position = sf::Vector2f(0, size.y);
}
