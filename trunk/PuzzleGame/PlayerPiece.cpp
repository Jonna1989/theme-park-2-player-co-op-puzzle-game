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

void PlayerPiece::Initialize(int boardHeight, int boardWidth)
{
	m_pieceOne = new Piece();
	m_pieceOne->Initialize();
	m_pieceOne->SetPosition(0,0);
	m_pieceTwo = new Piece();
	m_pieceTwo->Initialize();
	m_pieceTwo->SetPosition(0,1);
	m_boardHeight = boardHeight;
	m_boardWidth = boardWidth;
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
		if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //Aligned vertically
		{
			if((m_pieceOne->GetPosition().y > m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x < m_boardWidth - 1)) //Piece one below
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y + 1);
			}
			else if((m_pieceOne->GetPosition().y < m_pieceTwo->GetPosition().y) && m_pieceOne->GetPosition().x > 0) //Piece one above
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y - 1);
			}
		}
		else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y) //Aligned horisontally
		{
			if(m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x) //Piece one to the right
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y - 1);
			}
			else if((m_pieceOne->GetPosition().x < m_pieceTwo->GetPosition().x) && (m_pieceOne->GetPosition().y < m_boardHeight - 1)) //Piece one to the left
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y + 1);
			}
		}
	}
	else if (dir == -1)
	{
		if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //Aligned vertically
		{
			if((m_pieceOne->GetPosition().y > m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x > 0)) //Piece one below
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y + 1);
			}
			else if((m_pieceOne->GetPosition().y < m_pieceTwo->GetPosition().y) && m_pieceOne->GetPosition().x < m_boardWidth - 1) //Piece one above
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y - 1);
			}
		}
		else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y) //Aligned horisontally
		{
			if((m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x) && (m_pieceOne->GetPosition().y < m_boardHeight - 1)) //Piece one to the right
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y + 1);
			}
			else if(m_pieceOne->GetPosition().x < m_pieceTwo->GetPosition().x) //Piece one to the left
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y - 1);
			}
		}
	}
}

void PlayerPiece::MovePiece(int xDirection)
{
	if (xDirection == 1)
	{
		m_pieceOne->SetPosition(m_pieceOne->GetPosition().x+1,m_pieceOne->GetPosition().y);
		m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x+1,m_pieceTwo->GetPosition().y);
	}
	else if (xDirection == -1)
	{
		m_pieceOne->SetPosition(m_pieceOne->GetPosition().x-1,m_pieceOne->GetPosition().y);
		m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x-1,m_pieceTwo->GetPosition().y);
	}
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