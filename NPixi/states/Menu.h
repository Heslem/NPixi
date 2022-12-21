#pragma once

#include "IState.h"

class Menu sealed
	: public IState
{
public:

	Menu();
	~Menu();
	Menu(const Menu&) = delete;

	void update() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void renderImGui() override;

private:
	sf::RectangleShape m_Background;
	bool open;
};