#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "Board.h"

class Piece
{
public:
	Piece();
	~Piece();

	void Initialize(int owner);
	void Update();
	void Cleanup();

	int GetColor();
	sf::Vector2i GetPosition();
	//sf::Sprite* GetSprite();

	void SetColor(int color);
	void SetPosition(int posX, int posY);
	void SetOwner(int owner);

	void RandomizeColor();

private:
	Board* m_board;
	int m_color;
	int m_owner;
	sf::Vector2i m_position;
};

#endif