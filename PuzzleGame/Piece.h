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

	void Initialize(int owner, int marker);
	void Update();
	void Cleanup();

	int GetColor();
	sf::Vector2i GetPosition();
	int GetOwner();
	int GetMarker();

	void SetColor(int color);
	void SetPosition(int posX, int posY);
	void SetOwner(int owner);
	void SetMarker(int marker);

	int RandomizeColor();
	int NrOfAdjacentSameColor();
	std::vector<sf::Vector2i> PositionsOfAdjacentSameColor();

private:
	int m_color;
	int m_owner;
	int m_marker;
	sf::Vector2i m_position;
};

#endif