#pragma once

#include "../tiles/ChunkLoader.h"
#include "IState.h"
#include "../objects/entities/Player.h"
#include <vector>

#include "../utils/physics/QuadTree.h"

class World sealed
	: public IState
{
public:
	World(const bool& empty = false);
	~World();

	void update() override;
	void spawn(GameObject* object);

	void start() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void renderImGui() override;

	std::vector<GameObject*>& getObjects();

	std::vector<Collidable*> getCollisisionWithGameObject(GameObject* object);
	std::vector<Collidable*> computeCollisionGameObjects(GameObject* object);
private:

	QuadTree* m_QuadTree;
	std::vector<GameObject*> m_Objects;
	ChunkLoader* m_ChunkLoader;
};