#include "GameObject.h"

GameObject::GameObject(const objectId& id)
	: m_VertexArray(sf::PrimitiveType::Quads, 4), m_Alive(true), m_Fliped(false), m_IsMove(false), m_Id(id)
{
}

GameObject::~GameObject()
{
}

void GameObject::movePhysics(const float& x, const float& y)
{
	move(x, y);

	m_IsMove = true;

	if (x < 0) {
		flip(true);
	}
	else {
		flip(false);
	}
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (m_Texture != nullptr) states.texture = m_Texture;
	target.draw(m_VertexArray, states);
}

const sf::FloatRect GameObject::getCollision() const
{
	return sf::FloatRect(getPosition(), m_Size);
}

GameObject& GameObject::getGameObject()
{
	return *this;
}

void GameObject::setSize(const sf::Vector2f& size)
{
	m_VertexArray[0].position = sf::Vector2f(0, 0);
	m_VertexArray[1].position = sf::Vector2f(size.x, 0);
	m_VertexArray[2].position = sf::Vector2f(size.x, size.y);
	m_VertexArray[3].position = sf::Vector2f(0, size.y);

	m_Size = size;
}

void GameObject::setTexture(sf::Texture* texture)
{
	m_Texture = texture;

	sf::Vector2u size = texture->getSize();

	m_VertexArray[0].texCoords = sf::Vector2f(0, 0);
	m_VertexArray[1].texCoords = sf::Vector2f(size.x, 0);
	m_VertexArray[2].texCoords = sf::Vector2f(size.x, size.y);
	m_VertexArray[3].texCoords = sf::Vector2f(0, size.y);
}

void GameObject::onCollision(GameObject& collision)
{
}

void GameObject::flip(const bool& value)
{
	if (value == m_Fliped)
		return;
	m_Fliped = value;

	sf::Vector2u size = m_Texture->getSize();

	if (value) {
		m_VertexArray[0].texCoords = sf::Vector2f(size.x, 0);
		m_VertexArray[1].texCoords = sf::Vector2f(0, 0);
		m_VertexArray[2].texCoords = sf::Vector2f(0, size.y);
		m_VertexArray[3].texCoords = sf::Vector2f(size.x, size.y);
	}
	else {
		m_VertexArray[0].texCoords = sf::Vector2f(0, 0);
		m_VertexArray[1].texCoords = sf::Vector2f(size.x, 0);
		m_VertexArray[2].texCoords = sf::Vector2f(size.x, size.y);
		m_VertexArray[3].texCoords = sf::Vector2f(0, size.y);
	}
}

const bool& GameObject::isFlip() const noexcept
{
	return m_Fliped;
}
