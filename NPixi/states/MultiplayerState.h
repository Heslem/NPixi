#pragma once

#include "IState.h"

class MultiplayerState sealed
	: public IState
{
public:

	MultiplayerState();
	~MultiplayerState();
	MultiplayerState(const MultiplayerState&) = delete;

	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void renderImGui() override;

private:
	bool open;
	char* m_IpTextBuffer;
};