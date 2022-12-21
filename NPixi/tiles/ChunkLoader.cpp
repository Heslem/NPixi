#include "ChunkLoader.h"
#include "../Core.h"

#include "../utils/MathUtils.h"

ChunkLoader::ChunkLoader()
	: m_Seed(1)
{
	generate(noize::PerlinNoise());
}

ChunkLoader::~ChunkLoader()
{
	for (size_t i = 0; i < m_Chunks.size(); i++)
	{
		delete m_Chunks[i];
	}
}

void ChunkLoader::generateChunk(const float& x, const float& y, const noize::PerlinNoise& noise)
{
	Chunk* chunk = new Chunk(Core::getInstance().getAssetsManager().Textures["tilemap"], sf::Vector2f(x * CHUNK_SIZE_X * TILE_SIZE, y * CHUNK_SIZE_Y * TILE_SIZE), noise);
	m_Chunks.push_back(chunk);
}

void ChunkLoader::setTransformForDistance(sf::Transformable* transform)
{
	m_PlayerTransform = transform;
}

sf::Vector2i ChunkLoader::getPlayerChunk() const
{
	return getChunkByPosition(m_PlayerTransform->getPosition());
}

sf::Vector2i ChunkLoader::getChunkByPosition(const sf::Vector2f& position) const
{
	int pX = (int)(position.x / CHUNK_SIZE);
	int pY = (int)(position.y / CHUNK_SIZE);
	return sf::Vector2i(pX, pY);
}

void ChunkLoader::generate(const noize::PerlinNoise& noise)
{
	for (size_t i = 0; i < m_Chunks.size(); i++)
	{
		delete m_Chunks[i];
	}
	m_Chunks.clear();

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t x = 0; x < 5; x++)
		{

			generateChunk((float)x, (float)i, noise);
		}
	}
}

void ChunkLoader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < m_Chunks.size(); ++i)
	{
		if (m_PlayerTransform != nullptr) {
			//if (math::getDistance(m_Chunks[i]->getPosition(), m_PlayerTransform->getPosition()) < 800.0f)
				target.draw(*m_Chunks[i], states);
		}
		else {
			target.draw(*m_Chunks[i], states);
		}
	}
}
