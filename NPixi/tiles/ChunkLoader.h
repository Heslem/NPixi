#pragma once

#include "../sfml.h"
#include <vector>
#include "Chunk.h"
#include "../utils/PerlinNoize.h"

class ChunkLoader
	: public sf::Drawable
{
public:

	ChunkLoader();
	~ChunkLoader();
	ChunkLoader(const ChunkLoader&) = delete;

	void generateChunk(const float& x, const float& y, const noize::PerlinNoise& noise);
	void setTransformForDistance(sf::Transformable* transform);

	sf::Vector2i getPlayerChunk() const;
	sf::Vector2i getChunkByPosition(const sf::Vector2f& position) const;

	void generate(const noize::PerlinNoise& noise);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const int m_Seed;
	sf::Transformable* m_PlayerTransform;
	
	std::vector<Chunk*> m_Chunks;
};

