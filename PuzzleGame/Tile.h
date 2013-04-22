#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
public:
	Tile();
	~Tile();

	void Initialize(int tileSizeX, int tileSizeY, int vectorPosX, int vectorPosY);
	void Update();
	void Cleanup();

	sf::Vector2i GetTileSize();
	sf::Vector2f GetPositionPixels();
	sf::Vector2i GetPositionVector();
	int GetContent();
	int GetOwner();

	void SetTileSize(int x, int y);
	void SetPositionPixels(float x, float y);
	void SetPositionVector(int x, int y);
	void SetContent(int content);
	void SetOwner(int owner);

	void ClearTile();

private:
	sf::Vector2i m_tileSize;
	sf::Vector2f m_positionPixels;
	sf::Vector2i m_positionVector;
	int m_content;	
	int m_owner;
};

#endif