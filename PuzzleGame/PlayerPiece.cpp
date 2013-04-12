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
	m_pieceOne->SetPosition(0,0);
	m_pieceTwo = new Piece();
	m_pieceTwo->Initialize();
	m_pieceTwo->SetPosition(0,1);
}

void PlayerPiece::Update()
{

	m_pieceOne->Update();
	m_pieceTwo->Update();
	MovePiece(0);
}

void PlayerPiece::Cleanup()
{
	m_pieceOne->Cleanup();
	delete m_pieceOne;
	m_pieceTwo->Cleanup();
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

void PlayerPiece::MovePiece(int xDirection)
{
	float xSpeed = xDirection * 200 * DeltaTime;
	float ySpeed = 0*DeltaTime;
	m_pieceOne->GetSprite()->move(xSpeed,ySpeed);
	m_pieceTwo->GetSprite()->move(xSpeed,ySpeed);
}

void PlayerPiece::DropPiece()
{
	//-------------------------------------Write This, Idiots!--------------------------------- WHAT???
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