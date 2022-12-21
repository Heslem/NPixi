#include "Entity.h"

Entity::Entity(const objectId& id)
	: GameObject(id)
{
}

Entity::~Entity()
{
}

void Entity::entityMove(const float& x, const float& y)
{
	movePhysics(x * m_Speed, y * m_Speed);
}

void Entity::heal(const float& value)
{
	if (value < 0)
		return;

	m_Health += value;
}

void Entity::damage(const float& value)
{
	if (value < 0)
		return;

	m_Health -= value;
}

void Entity::eat(const float& value)
{
	if (value < 0)
		return;

	m_Food += value;
}

void Entity::hunger(const float& value)
{
	if (value < 0)
		return;

	m_Food -= value;
}

void Entity::setTemperature(const float& temperature)
{
	// TODO: add death from temperature
	m_Temperature = temperature;
}

void Entity::setFood(const float& value)
{
	if (value < 0)
		destroy();

	m_Food = value;
}

void Entity::setSpeed(const float& value)
{
	if (value < 0)
		return;
	m_Speed = value;
}
