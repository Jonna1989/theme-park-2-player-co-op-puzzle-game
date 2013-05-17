#include "Tile.h"

#pragma region Base
Tile::Tile()
{
	m_content = NULL;
	m_owner = NULL;
	m_previousOwner = NULL;
	m_isFalling = NULL;
	m_halfStep = NULL;
	m_marker = NULL;
}


Tile::~Tile()
{
}

void Tile::Initialize(int tileSizeX, int tileSizeY, int vectorPosX, int vectorPosY)
{
	m_tileSize.x = tileSizeX;
	m_tileSize.y = tileSizeY;
	m_positionVector.x = vectorPosX;
	m_positionVector.y = vectorPosY;
	SetPositionPixels(((float)m_positionVector.x * m_tileSize.x), ((float)m_positionVector.y * m_tileSize.y));
	m_content = 0;
	m_owner = 0;
	m_previousOwner = 0;
	m_isFalling = false;
	m_halfStep = 0;
	m_marker = 0;
}

void Tile::Update()
{
}

void Tile::Cleanup()
{
}
#pragma endregion

#pragma region Getters

sf::Vector2i Tile::GetTileSize()
{
	return m_tileSize;
}

sf::Vector2f Tile::GetPositionPixels()
{
	return m_positionPixels;
}

sf::Vector2i Tile::GetPositionVector()
{
	return m_positionVector;
}

int Tile::GetContent()
{
	return m_content;
}

int Tile::GetOwner()
{
	return m_owner;
}

int Tile::GetPreviousOwner()
{
	return m_previousOwner;
}
int Tile::GetMarker()
{
	return m_marker;
}
#pragma endregion

#pragma region Setters

void Tile::SetTileSize(int x, int y)
{
	m_tileSize.x = x;
	m_tileSize.y = y;
}

void Tile::SetPositionPixels(float x, float y)
{
	m_positionPixels.x = x;
	m_positionPixels.y = y;
}

void Tile::SetPositionVector(int x, int y)
{
	m_positionVector.x = x;
	m_positionVector.y = y;
	SetPositionPixels(((float)m_positionVector.x * m_tileSize.x), ((float)m_positionVector.y * m_tileSize.y));
}

void Tile::SetContent(int content)
{
	m_content = content;
}

void Tile::SetOwner(int owner)
{
	m_owner = owner;
}

void Tile::SetPreviousOwner(int previousOwner)
{
	m_previousOwner = previousOwner;
}
void Tile::SetMarker(int marker)
{
	m_marker = marker;
}
#pragma endregion

void Tile::ClearTile()
{
	SetContent(0);
	SetOwner(0);
}
void Tile::SetFalling(bool isfalling)
{
	m_isFalling = isfalling;
}
bool Tile::GetFalling()
{
	return m_isFalling;
}
void Tile::SetHalfStep(int halfStep)
{
	m_halfStep = halfStep;
}
int Tile::GetHalfStep()
{
	return m_halfStep;
}