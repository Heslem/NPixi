#pragma once

#include "Entity.h"
#include "../../ann/neural_network.h"

class Villager sealed :
	public Entity
{
public:
	Villager();
	~Villager();
	Villager(const Villager&) = delete;

	void update() override;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	neural_network m_NeuralNetwork;
};