#include "Thorn.h"

#pragma region Base
Thorn::Thorn()
{
	m_isFalling = true;
	m_isInitialized = false;
	m_hasActivated = false;
}


Thorn::~Thorn()
{
}

void Thorn::Initialize()
{
	m_position.x = 0;
	m_position.y = 0;
	m_isFalling = true;
	m_goodItem = true;
	m_contentID = NUMBER_OF_BUBBLES + 3;
	m_isInitialized = true;
	m_hasActivated = false;
}

void Thorn::Update()
{
	Drop();

	if(m_position.y < BOARD_HEIGHT && !m_hasActivated)
	{
		Activate();
	}
}

void Thorn::Cleanup()
{
	Board::Instance()->GetTile(m_position.x, m_position.y)->ClearTile();
}

#pragma endregion

#pragma region Actions

void Thorn::Activate()
{
	if(m_position.y + 1 < BOARD_HEIGHT)
	{
		Board::Instance()->GetTile(m_position.x, m_position.y + 1)->ClearTile();
		m_position.y = m_position.y + 1;
	}
	else
	{
		m_hasActivated = true;
	}	
}

void Thorn::Drop()
{
	if(m_position.y + 1 < BOARD_HEIGHT)
	{
		if(Board::Instance()->IsTileVacant(m_position.x, m_position.y + 1))
		{
			Board::Instance()->DropTile(m_position.x, m_position.y);
			m_position.y = m_position.y + 1;
		}
	}
	else if(m_position.y + 1 == BOARD_HEIGHT)
	{
		m_isFalling = false;
	}
}

#pragma endregion