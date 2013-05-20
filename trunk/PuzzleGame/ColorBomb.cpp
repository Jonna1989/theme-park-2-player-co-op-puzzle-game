#include "ColorBomb.h"

#pragma region Base

ColorBomb::ColorBomb()
{
	m_isFalling = true;
	m_isInitialized = false;
	m_hasActivated = false;
	m_colorToRemove = NULL;
}


ColorBomb::~ColorBomb()
{
}

void ColorBomb::Initialize()
{
	m_position.x = 0;
	m_position.y = 0;
	m_isFalling = true;
	m_goodItem = true;
	m_contentID = NUMBER_OF_BUBBLES + 2;
	m_colorToRemove = 0;
	m_isInitialized = true;
	m_hasActivated = false;
}

void ColorBomb::Update()
{
	Drop();

	if(!m_isFalling && !m_hasActivated)
	{
		Activate();
	}
}

void ColorBomb::Cleanup()
{
	Board::Instance()->GetTile(m_position.x, m_position.y)->ClearTile();
}

#pragma endregion

#pragma region Actions

void ColorBomb::Activate()
{
	std::vector<sf::Vector2i> tilesToRemove;

	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			if(Board::Instance()->GetColor(x, y) == m_colorToRemove)
			{
				tilesToRemove.push_back(sf::Vector2i(x, y));
			}
		}
	}

	for(unsigned int i = 0; i < tilesToRemove.size(); i++)
	{
		Board::Instance()->GetTile(tilesToRemove.at(i).x, tilesToRemove.at(i).y)->ClearTile();
	}

	m_hasActivated = true;
	Board::Instance()->GetTile(m_position.x, m_position.y)->ClearTile();
}

#pragma endregion

#pragma region Getters

int ColorBomb::GetColorToRemove()
{
	return m_colorToRemove;
}

#pragma endregion

#pragma region Setters

void ColorBomb::SetColorToRemove(int color)
{
	m_colorToRemove = color;
}

#pragma endregion