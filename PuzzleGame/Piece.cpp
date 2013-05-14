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

void Piece::Initialize(int owner, int marker)
{
	m_color = RandomizeColor();
	m_position = sf::Vector2i(-1, -1);

	m_owner = owner;
	m_marker = marker;
}

void Piece::Update()
{
	
}

void Piece::Cleanup()
{
}

int Piece::GetColor()
{
	return m_color;
}

sf::Vector2i Piece::GetPosition()
{
	return m_position;
}

int Piece::GetOwner()
{
	return m_owner;
}
int Piece::GetMarker()
{
	return m_marker;
}
void Piece::SetColor(int color)
{
	m_color = color;

	if(m_position.x != -1 && m_position.y != -1)
	{
		Board::Instance()->SetColor(m_position.x, m_position.y, color);
	}
}

void Piece::SetPosition(int posX, int posY)
{
	if(m_position.x != -1 && m_position.y != -1)
	{
		Board::Instance()->SetOwner(m_position.x, m_position.y, 0);
		Board::Instance()->SetColor(m_position.x, m_position.y, 0);
	}
	
	m_position.x = posX;
	m_position.y = posY;
	Board::Instance()->SetOwner(m_position.x, m_position.y, m_owner);
	Board::Instance()->SetColor(m_position.x, m_position.y, m_color);
}

void Piece::SetOwner(int owner)
{
	m_owner = owner;
	Board::Instance()->SetOwner(m_position.x, m_position.y, m_owner);
}
void Piece::SetMarker(int marker)
{
	m_marker = marker;
}
#pragma endregion

#pragma region Publics

int Piece::RandomizeColor()
{
	return (rand () % (8 - 1) + 1);
}

int Piece::NrOfAdjacentSameColor()
{
	int sameColor = 0; 

	if(m_position.y - 1 >= 0)
	{
		if(Board::Instance()->GetColor(m_position.x, m_position.y - 1) == m_color)
		{
			sameColor++;
		}
	}

	if(m_position.x + 1 < BOARD_WIDTH)
	{
		if(Board::Instance()->GetColor(m_position.x + 1, m_position.y) == m_color)
		{
			sameColor++;
		}
	}

	if(m_position.y + 1 < BOARD_HEIGHT)
	{
		if(Board::Instance()->GetColor(m_position.x, m_position.y + 1) == m_color)
		{
			sameColor++;
		}
	}

	if(m_position.x - 1 >= 0)
	{
		if(Board::Instance()->GetColor(m_position.x - 1, m_position.y) == m_color)
		{
			sameColor++;
		}
	}

	return sameColor;
}

std::vector<sf::Vector2i> Piece::PositionsOfAdjacentSameColor()
{
	std::vector<sf::Vector2i> sameColorPositions; 

	if(m_position.y - 1 >= 0)
	{
		if(Board::Instance()->GetColor(m_position.x, m_position.y - 1) == m_color)
		{
			sameColorPositions.push_back(sf::Vector2i(m_position.x, m_position.y - 1));
		}
	}

	if(m_position.x + 1 < BOARD_WIDTH)
	{
		if(Board::Instance()->GetColor(m_position.x + 1, m_position.y) == m_color)
		{
			sameColorPositions.push_back(sf::Vector2i(m_position.x + 1, m_position.y));
		}
	}

	if(m_position.y + 1 < BOARD_HEIGHT)
	{
		if(Board::Instance()->GetColor(m_position.x, m_position.y + 1) == m_color)
		{
			sameColorPositions.push_back(sf::Vector2i(m_position.x, m_position.y + 1));
		}
	}

	if(m_position.x - 1 >= 0)
	{
		if(Board::Instance()->GetColor(m_position.x - 1, m_position.y) == m_color)
		{
			sameColorPositions.push_back(sf::Vector2i(m_position.x - 1, m_position.y));
		}
	}

	return sameColorPositions;
}

#pragma endregion