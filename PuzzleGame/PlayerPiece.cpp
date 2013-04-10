#include "PlayerPiece.h"

#pragma region Base

PlayerPiece::PlayerPiece()
{
}


PlayerPiece::~PlayerPiece()
{
}

#pragma endregion

#pragma region Publics

void PlayerPiece::Initialize()
{
	m_pieceOne = new Piece();
	m_pieceOne->Initialize();

	m_pieceTwo = new Piece();
	m_pieceTwo->Initialize();
	m_pieceTwo->GetSprite()->setPosition(m_pieceOne->GetPosition().x,m_pieceOne->GetPosition().y-100);
}

void PlayerPiece::Update()
{
	m_pieceOne->Update();
	m_pieceTwo->Update();
}

void PlayerPiece::Cleanup()
{
	delete m_pieceOne;
	delete m_pieceTwo;
}

void PlayerPiece::RotatePiece(int dir)
{
	if (dir == 1)
	{
		//ROTATE RIGHT, MORE LIKE MOVE THE SECOND BLOCK IN A FASHIONABLE WAY TO THE RIGHT WAY AROUND THE FIRST BLOCK
	}
	else if (dir == -1)
	{
		//ROTATE LEFT, MORE LIKE MOVE THE SECOND BLOCK IN A FASHIONABLE WAY TO THE LEFT WAY AROUND THE FIRST BLOCK
	}
}

void PlayerPiece::MovePiece()
{
	float speed = 200*DeltaTime;
	m_pieceOne->GetSprite()->move(0,speed);
	m_pieceTwo->GetSprite()->move(0,speed);
}

void PlayerPiece::SetPieces(int valueOne, int valueTwo)
{
	m_pieceOne->SetValue(valueOne);
	m_pieceTwo->SetValue(valueTwo);
}

Piece* PlayerPiece::GetPieceOne()
{
	return m_pieceOne;
}

Piece* PlayerPiece::GetPieceTwo()
{
	return m_pieceTwo;
}

#pragma endregion