#include "Chunk.h"
#include <iostream>

#include <random>


Chunk::Chunk(sf::Texture* tilemapTexture, const sf::Vector2f& position, noize::PerlinNoise noise)
	: m_VertexArray(sf::PrimitiveType::Quads, 0), m_Texture(tilemapTexture)
{
	
	double noiseArray[CHUNK_SIZE_X][CHUNK_SIZE_Y];

	for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
		for (int x = 0; x < CHUNK_SIZE_X; ++x) {
			double n = noise.ValueNoise_2D(x + position.x , y + position.y);

			tile_type t;

			if (n > 0.21) {
				t = tile_type::SNOW;
			}
			else if (n > 0.15) {
				t = tile_type::TILE_STONE;
			}
			else if (n > 0.02) {
				t = tile_type::TILE_GRASS;
			}
			else if (n > 0.0) {
				t = tile_type::TILE_DIRT;
			}
			else if (n < -0.1) {
				t = tile_type::TILE_VERY_DEEP_WATER;
			}
			else if (n < -0.03) {
				t = tile_type::TILE_DEEP_WATER;
			}
			else if (n < 0.0) {
				t = tile_type::WATER;
			}
			setTile(x, y, t);
		}
	}

	update();
	setPosition(position);
}

Chunk::~Chunk()
{
}

const tile_type& Chunk::getTile(const int& x, const int& y) const
{
	return m_Tiles[x + (y * CHUNK_SIZE_X)];
}

void Chunk::setTile(const int& x, const int& y, const tile_type& type)
{
	m_Tiles[x + (y * CHUNK_SIZE_X)] = type;
}

void Chunk::update()
{
	m_VertexArray.clear();
	for (int y = 0; y < CHUNK_SIZE_Y; ++y)
	{
		for (int x = 0; x < CHUNK_SIZE_X; ++x)
		{
			addTileToVertexArray(x * TILE_SIZE, y * TILE_SIZE, getTile(x, y));
		}
	}
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = m_Texture;
	states.transform *= getTransform();
	target.draw(m_VertexArray, states);
}

void Chunk::addTileToVertexArray(const int& x, const int& y, const tile_type& type)
{
	sf::Vector2f texPosition = getTilePositionInTexture(type);

	m_VertexArray.append(sf::Vertex(sf::Vector2f(x, y), sf::Vector2f(texPosition.x, texPosition.y)));
	m_VertexArray.append(sf::Vertex(sf::Vector2f(x + TILE_SIZE, y) , sf::Vector2f(texPosition.x + TILE_TEXTURE_SIZE, texPosition.y)));
	m_VertexArray.append(sf::Vertex(sf::Vector2f(x + TILE_SIZE, y + TILE_SIZE), sf::Vector2f(texPosition.x + TILE_TEXTURE_SIZE, texPosition.y + TILE_TEXTURE_SIZE)));
	m_VertexArray.append(sf::Vertex(sf::Vector2f(x, y + TILE_SIZE), sf::Vector2f(texPosition.x, texPosition.y + TILE_TEXTURE_SIZE)));
}

const sf::Vector2f Chunk::getTilePositionInTexture(const tile_type& type)
{
	return sf::Vector2f((float)((int)type * TILE_TEXTURE_SIZE), 0);
}
