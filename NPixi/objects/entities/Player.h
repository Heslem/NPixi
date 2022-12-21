#pragma once

#include "Entity.h"

class World;

class Player sealed :
	public Entity
{
public:
	explicit Player(const bool& controlled = true);
	~Player();
	Player(const Player&) = delete;

	void update() override;
private:

	bool m_Controlled;
	World& m_World;
};