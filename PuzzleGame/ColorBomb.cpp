#include "ColorBomb.h"

#pragma region Base

ColorBomb::ColorBomb()
{
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
	m_colorToRemove = 0;
}

void ColorBomb::Update()
{

}

void ColorBomb::Cleanup()
{
	
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