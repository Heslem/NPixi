#include "IState.h"

IState::IState(const char* name) :
	m_Name(name)
{
}

IState::~IState()
{
}

void IState::start()
{
}

void IState::end()
{
}

void IState::renderImGui()
{
}

const char* IState::getName() const noexcept
{
	return m_Name;
}

std::string IState::getNameString() const
{
	return m_Name;
}
