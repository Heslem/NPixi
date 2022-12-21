#pragma once

#include "../GameObject.h"

class Entity 
	: public GameObject
{
public:
	Entity(const objectId& id);
	virtual ~Entity();

	const float& getHealth() const noexcept { return m_Health; }
	const float& getSpeed() const noexcept { return m_Speed; }
	const float& getFood() const noexcept { return m_Food; }
	const float& getTemperature() const noexcept { return m_Temperature; }

	void entityMove(const float& x, const float& y);
	void heal(const float& value);
	void damage(const float& value);
	void eat(const float& value);
	void hunger(const float& value);

	void setTemperature(const float& temperature);
	void setFood(const float& value);
	void setSpeed(const float& value);

private:
	float m_Health = 100.0f;
	float m_Temperature = 36.0f;
	float m_Food = 100.f;
	float m_Speed = 1.0f;
};