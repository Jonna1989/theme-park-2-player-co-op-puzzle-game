#include "PowerItem.h"

#pragma region Base

PowerItem::PowerItem()
{
}


PowerItem::~PowerItem()
{
}

#pragma endregion

#pragma region Actions

void PowerItem::Drop()
{
	if(m_isFalling)
	{
		if(m_position.y + 1 < BOARD_HEIGHT)
		{
			if(Board::Instance()->IsTileVacant(m_position.x, m_position.y + 1))
			{
				m_position.y = m_position.y + 1;
			}
			else if(Board::Instance()->GetOwner(m_position.x, m_position.y + 1) == 0)
			{
				m_isFalling = false;
			}
		}
		else if(m_position.y + 1 == BOARD_HEIGHT)
		{
			m_isFalling = false;
		}
	}
}

#pragma endregion

#pragma region Getters

sf::Vector2i PowerItem::GetPosition()
{
	return m_position;
}

bool PowerItem::IsFalling()
{
	return m_isFalling;
}

bool PowerItem::IsGoodItem()
{
	return m_goodItem;
}

int PowerItem::GetContentID()
{
	return m_contentID;
}

bool PowerItem::GetIsInitialized()
{
	return m_isInitialized;
}

bool PowerItem::HasActivated()
{
	return m_hasActivated;
}

#pragma endregion

#pragma region Setters

void PowerItem::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;

	Board::Instance()->SetColor(x, y, m_contentID);
}

void PowerItem::SetFalling(bool falling)
{
	m_isFalling = falling;
}

void PowerItem::SetGoodItem(bool good)
{
	m_goodItem = good;
}

void PowerItem::SetContentID(int ID)
{
	m_contentID = ID;
}

void PowerItem::SetHasActivated(bool activated)
{
	 m_hasActivated = activated;
}

#pragma endregion