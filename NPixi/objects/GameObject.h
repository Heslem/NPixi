#pragma once

#include "../sfml.h"
#include "../utils/physics/QuadTree.h"
#include "objectId.h"

class GameObject
	: public sf::Transformable, public sf::Drawable, public Collidable
{
public:
	GameObject(const objectId& id);
	virtual ~GameObject();

	virtual void update() = 0;

	/// <summary>
	/// Flip sprite and compute collisions.
	/// </summary>
	void movePhysics(const float& x, const float& y);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void flip(const bool& value);
	const bool& isFlip() const noexcept;

	void setSize(const sf::Vector2f& size);
	void setTexture(sf::Texture* texture);

	void onCollision(GameObject& collision) override;

	const sf::FloatRect getCollision() const override;
	GameObject& getGameObject() override;

	const bool& isAlive() const noexcept { return m_Alive; }
	void destroy() { m_Alive = false; }
	const bool& isMove() const noexcept { return m_IsMove; }
	const objectId& getId() const noexcept { return m_Id; }
private:
	sf::VertexArray m_VertexArray;
	sf::Texture* m_Texture;
	sf::Color m_Color;
	sf::Vector2f m_Size;
	bool m_Fliped;
	bool m_Alive;
	bool m_IsMove;
	const objectId m_Id;
};