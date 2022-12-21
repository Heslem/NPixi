#pragma once

#include "../sfml.h"

class IState :
	public sf::Drawable
{
public: 

	IState(const char* name);
	virtual ~IState();

	virtual void start();
	virtual void end();
	virtual void update() = 0;
	virtual void renderImGui();
	// Don't forget override - void draw(sf::RenderTarget& target, sf::RenderStates states) const

	const char* getName() const noexcept;
	std::string getNameString() const;
private:

	const char* m_Name;
};

