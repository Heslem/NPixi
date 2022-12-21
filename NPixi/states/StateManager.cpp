#include "StateManager.h"

#include "Menu.h"

#include <iostream>

StateManager::StateManager()
	: m_CurrentState(nullptr)
{
	Menu* menu = new Menu();
	addState(menu);

	setCurrentState("menu");
}

StateManager::~StateManager()
{
	std::cout << "Delete states." << std::endl;
	for (size_t i = 0; i < m_States.size(); ++i)
	{
		delete m_States[i];
	}
}

void StateManager::update()
{
	m_CurrentState->update();
}

void StateManager::addState(IState* state)
{
	m_States.push_back(state);
}

IState* StateManager::getState(const char* name)
{
	for (size_t i = 0; i < m_States.size(); ++i)
	{
		if (m_States[i]->getName() == name) {
			return m_States[i];
			break;
		}
	}
	return nullptr;
}

void StateManager::setCurrentState(const char* name)
{
	for (size_t i = 0; i < m_States.size(); ++i)
	{
		if (m_States[i]->getName() == name) {
			m_CurrentState = m_States[i];
			m_CurrentState->start();
			break;
		}
	}
}

IState& StateManager::getCurrentState()
{
	return *m_CurrentState;
}

void StateManager::renderImGui()
{
	m_CurrentState->renderImGui();
}

void StateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_CurrentState, states);
}
