#include "Bomb.h"

#pragma region Base

Bomb::Bomb()
{
	m_isFalling = true;
	m_isInitialized = false;
	m_hasActivated = false;
	m_blastRadius = NULL;
}


Bomb::~Bomb()
{
}

void Bomb::Initialize()
{
	m_position.x = 0;
	m_position.y = 0;
	m_isFalling = true;
	m_goodItem = true;
	m_blastRadius = 2;
	m_contentID = 11;
	m_isInitialized = true;
	m_hasActivated = false;
}

void Bomb::Update()
{
	Drop();

	if(!m_isFalling && !m_hasActivated)
	{
		Activate();
	}
}

void Bomb::Cleanup()
{

}

#pragma endregion

#pragma region Actions

void Bomb::Activate()
{
	std::vector<sf::Vector2i> tilesToClear;

	for(int y = m_position.y - m_blastRadius; y <= m_position.y + m_blastRadius; y++)
	{
		for(int x = m_position.x - m_blastRadius; x <= m_position.x + m_blastRadius; x++)
		{
			if((y > 0 && y < BOARD_HEIGHT) && (x > 0 && x < BOARD_WIDTH))
			{
				tilesToClear.push_back(sf::Vector2i(x, y));
			}
		}
	}

	for(unsigned int i = 0; i < tilesToClear.size(); i++)
	{
		Board::Instance()->GetTile(tilesToClear.at(i).x, tilesToClear.at(i).y)->ClearTile();
	}

	m_hasActivated = true;
	Board::Instance()->GetTile(m_position.x, m_position.y)->ClearTile();
}

#pragma endregion

#pragma region Getters

int Bomb::GetBlastRadius()
{
	return m_blastRadius;
}

#pragma endregion

#pragma region Setters

void Bomb::SetBlastRadius(int blastRadius)
{
	m_blastRadius = blastRadius;
}

#pragma endregion