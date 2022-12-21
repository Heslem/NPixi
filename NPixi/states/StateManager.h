#pragma once

#include "IState.h"
#include <vector>

class StateManager sealed
	: public sf::Drawable
{
public:
	StateManager();
	~StateManager();

	void update();
	
	void addState(IState* state);
	IState* getState(const char* name);
	void setCurrentState(const char* name);
	IState& getCurrentState();

	void renderImGui();
private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	IState* m_CurrentState;

	std::vector<IState*> m_States;
};