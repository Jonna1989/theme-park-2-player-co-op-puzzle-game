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
	srand((int)time((0)));

	m_value = (rand () % (5 - 1) + 1);
	m_position = sf::Vector2i(0,0);

	m_pieceTexture = new sf::Texture();
	m_pieceSprite = new sf::Sprite();

	std::stringstream ballStream;
	ballStream << m_value;

	m_pieceTexture->loadFromFile("Assets/GraphicalAssets/Art/ball"+ballStream.str()+".png");
	m_pieceSprite->setTexture(*m_pieceTexture);
}

void Piece::Update()
{
	m_position.x = (int)m_pieceSprite->getPosition().x/100;
	m_position.y = (int)m_pieceSprite->getPosition().y/100;
}

void Piece::Cleanup()
{
	delete m_pieceTexture;
	delete m_pieceSprite;
}

int Piece::GetValue()
{
	return m_value;
}

sf::Vector2i Piece::GetPosition()
{
	return m_position;
}

sf::Sprite* Piece::GetSprite()
{
	return m_pieceSprite;
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