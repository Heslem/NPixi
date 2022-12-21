#pragma once

#include "../sfml.h"
#include "tile_type.h"
#include "../utils/PerlinNoize.h"

constexpr int TILE_TEXTURE_SIZE = 16;
constexpr int TILE_SIZE = 64;
constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 16;
constexpr int CHUNK_SIZE = CHUNK_SIZE_X * CHUNK_SIZE_Y;

class Chunk sealed :
	public sf::Transformable, public sf::Drawable 
{
public:

	Chunk(sf::Texture* tilemapTexture, const sf::Vector2f& position, noize::PerlinNoise noise);
	~Chunk();
	Chunk(const Chunk&) = delete;

	const tile_type& getTile(const int& x, const int& y) const;
	void setTile(const int& x, const int& y, const tile_type& type);
	void update();

private:
	void addTileToVertexArray(const int& x, const int& y, const tile_type& type);
	static const sf::Vector2f getTilePositionInTexture(const tile_type& type);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture* m_Texture;
	tile_type m_Tiles[CHUNK_SIZE];
	sf::VertexArray m_VertexArray;
};