#pragma once
#include "IState.h"

class ServerState sealed
	: public IState
{
public:
	ServerState();
	~ServerState();

	void update() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

};