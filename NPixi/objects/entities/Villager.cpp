#include "Villager.h"

#include "../../Core.h"

Villager::Villager()
	: Entity(VILLAGER),m_NeuralNetwork(2, 2, 2, 2)
{
	setSize(sf::Vector2f(40, 40));
	setTexture(Core::getInstance().getAssetsManager().Textures["bot"]);
}

Villager::~Villager()
{
}

void Villager::update()
{
}

void Villager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
}
