#pragma once

#include "../sfml.h"

class GameObject; 

class ICollisiable {
public:
	virtual const sf::FloatRect getCollision() const = 0;
	virtual GameObject& getGameObject() = 0;
};