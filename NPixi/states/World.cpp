#include "World.h"

#include "../Core.h"
#include <iostream>
#include "../imgui/imgui.h"
#include "../imgui/imgui-sfml.h"

#include "../utils/PerlinNoize.h"

#include "../objects/entities/Villager.h"

World::World(const bool& empty)
	: IState("world")
{
	m_ChunkLoader = new ChunkLoader();
	//m_QuadTree = new QuadTree(sf::FloatRect(0, 0, 2000, 2000), 2 , 4);
	

	if (!empty) {
	}

	Core::getInstance().getLuaBinding().doAllScripts(*this);
}

World::~World()
{
	delete m_ChunkLoader;
	//delete m_QuadTree;
}

void World::update()
{
	/*for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		if (m_Objects[i]->isMove()) {
			m_QuadTree->update(m_Objects[i]);
		}
	}*/


	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		/*auto objects = m_QuadTree->getObjectsInBound_unchecked(m_Objects[i]->getCollision());
		const auto rect = m_Objects[i]->getCollision();

		for (size_t x = 0; x < objects.size(); ++x)
		{
			if (rect.intersects(objects[x]->getCollision())) {
				m_Objects[i]->onCollision(objects[x]->getGameObject());
			}
		}*/


		if (!m_Objects[i]->isAlive()) {
			delete m_Objects[i];
			m_Objects.erase(m_Objects.begin() + i);
		}
		else {
			m_Objects[i]->update();
			
		}
	}

}

void World::spawn(GameObject* object)
{
	m_Objects.push_back(object);
	//m_QuadTree->insert(object);
}

void World::start()
{
	auto* player = new Player();
	spawn(player);
	Core::getInstance().getCamera().bind(*player);
	m_ChunkLoader->setTransformForDistance(player);

	
	for (size_t i = 0; i < 10; i++)
	{
		Villager* villager = new Villager();
		villager->setPosition(sf::Vector2f(i * 50, 0));
		spawn(villager);
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_ChunkLoader, states);
	
	for (size_t i = 0; i < m_Objects.size(); ++i)
	{
		target.draw(*m_Objects[i], states);
	}

	//target.draw(*m_QuadTree);
}

void World::renderImGui()	
{

	static noize::PerlinNoise noise;

	ImGui::Begin(u8"Генератор", (bool*)0, ImGuiWindowFlags_AlwaysAutoResize);
	for (size_t i = 0; i < noize::maxPrimeIndex; i++)
	{
		for (size_t y = 0; y < 3; y++)
		{
			ImGui::InputInt((std::to_string(i) + std::to_string(y)).c_str(), &noise.primes[i][y]);
		}
		
	}
	ImGui::InputInt(u8"Октавы", &noise.numOctaves);
	ImGui::InputDouble(u8"Настойчивость", &noise.persistence);
	 
	if (ImGui::Button(u8"Сгенерировать")) {

		m_ChunkLoader->generate(noise);
	}
	ImGui::End();
}

std::vector<GameObject*>& World::getObjects()
{
	return m_Objects;
}

std::vector<Collidable*> World::getCollisisionWithGameObject(GameObject* object)
{
	
	return m_QuadTree->getObjectsInBound_unchecked(object->getCollision());;
}

std::vector<Collidable*> World::computeCollisionGameObjects(GameObject* object)
{
	return std::vector<Collidable*>();
}
