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

void Piece::Initialize(int owner)
{
	srand((int)time((0)));

	m_color = (rand () % (5 - 1) + 1);
	m_position = sf::Vector2i(-1, -1);

	m_pieceTexture = new sf::Texture();
	m_pieceSprite = new sf::Sprite();

	std::stringstream ballStream;
	ballStream << m_color;

	m_pieceTexture->loadFromFile("Assets/GraphicalAssets/TempArt/ball"+ballStream.str()+".png");
	m_pieceSprite->setTexture(*m_pieceTexture);

	m_board = Board::Instance();
	m_owner = owner;
}

void Piece::Update()
{
	
}

void Piece::Cleanup()
{
	delete m_pieceTexture;
	delete m_pieceSprite;
}

int Piece::GetColor()
{
	return m_color;
}

sf::Vector2i Piece::GetPosition()
{
	return m_position;
}

sf::Sprite* Piece::GetSprite()
{
	return m_pieceSprite;
}

void Piece::SetColor(int color)
{
	m_color = color;

	if(m_position.x != -1 && m_position.y != -1)
	{
		m_board->SetColor(m_position.x, m_position.y, color);
	}
}

void Piece::SetPosition(int posX, int posY)
{
	if(m_position.x != -1 && m_position.y != -1)
	{
		m_board->SetOwner(m_position.x, m_position.y, 0);
		m_board->SetColor(m_position.x, m_position.y, 0);
	}
	
	m_position.x = posX;
	m_position.y = posY;
	m_board->SetOwner(m_position.x, m_position.y, m_owner);
	m_board->SetColor(m_position.x, m_position.y, m_color);
	m_pieceSprite->setPosition(posX*50,posY*50);
}

void Piece::SetOwner(int owner)
{
	m_owner = owner;
	m_board->SetOwner(m_position.x, m_position.y, m_owner);
}

#pragma endregion