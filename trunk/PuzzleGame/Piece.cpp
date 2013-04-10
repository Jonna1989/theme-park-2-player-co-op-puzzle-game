#include "Piece.h"

#pragma region Base

Piece::Piece()
{
}


Piece::~Piece()
{
}

#pragma endregion

#pragma region Publics

void Piece::Initialize()
{
	srand(time((0)));

	m_value = rand () % (5 - 1 + 1);
	m_position = sf::Vector2i(0,0);
}

void Piece::Update()
{

}

void Piece::Cleanup()
{

}

int Piece::GetValue()
{
	return m_value;
}

sf::Vector2i Piece::GetPosition()
{
	return m_position;
}

void Piece::SetValue(int value)
{
	m_value = value;
}

void Piece::SetPosition(int posX, int posY)
{
	m_position = sf::Vector2i(posX,posY);
}

#pragma endregion