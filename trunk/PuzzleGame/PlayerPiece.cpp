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

void PlayerPiece::Initialize(int owner)
{
	m_board = Board::Instance();
	m_owner = owner;

	if(m_owner == 10)
	{
		m_pieceOne = new Piece();
		m_pieceOne->Initialize(m_owner);
		m_pieceOne->SetPosition(0 , 0);
		m_pieceTwo = new Piece();
		m_pieceTwo->Initialize(m_owner);
		m_pieceTwo->SetPosition(0, 1);
	}
	else if(m_owner == 20)
	{
		m_pieceOne = new Piece();
		m_pieceOne->Initialize(m_owner);
		m_pieceOne->SetPosition(BOARD_WIDTH - 1 , 0);
		m_pieceTwo = new Piece();
		m_pieceTwo->Initialize(m_owner);
		m_pieceTwo->SetPosition(BOARD_WIDTH - 1, 1);
	}
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
			if((m_pieceOne->GetPosition().y > m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x < BOARD_WIDTH - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y + 1))) //Piece one below
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y + 1);
			}
			else if((m_pieceOne->GetPosition().y < m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x > 0)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y - 1))) //Piece one above
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y - 1);
			}
		}
		else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y) //Aligned horisontally
		{
			if((m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y - 1))) //Piece one to the right
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y - 1);
			}
			else if((m_pieceOne->GetPosition().x < m_pieceTwo->GetPosition().x) && (m_pieceOne->GetPosition().y < BOARD_HEIGHT - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y + 1))) //Piece one to the left
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y + 1);
			}
		}
	}
	else if (dir == -1)
	{
		if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //Aligned vertically
		{
			if((m_pieceOne->GetPosition().y > m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x > 0)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y + 1))) //Piece one below
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y + 1);
			}
			else if((m_pieceOne->GetPosition().y < m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x < BOARD_WIDTH - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y - 1))) //Piece one above
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y - 1);
			}
		}
		else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y) //Aligned horisontally
		{
			if((m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x) && (m_pieceOne->GetPosition().y < BOARD_HEIGHT - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y + 1))) //Piece one to the right
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y + 1);
			}
			else if(m_pieceOne->GetPosition().x < (m_pieceTwo->GetPosition().x)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y - 1))) //Piece one to the left
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
		if((m_pieceOne->GetPosition().x < BOARD_WIDTH - 1) && m_pieceTwo->GetPosition().x < BOARD_WIDTH - 1)
		{
			m_pieceOne->SetPosition(m_pieceOne->GetPosition().x+1,m_pieceOne->GetPosition().y);
			m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x+1,m_pieceTwo->GetPosition().y);
		}
	}
	else if (xDirection == -1)
	{
		if((m_pieceOne->GetPosition().x > 0) && m_pieceTwo->GetPosition().x > 0)
		{
			m_pieceOne->SetPosition(m_pieceOne->GetPosition().x-1,m_pieceOne->GetPosition().y);
			m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x-1,m_pieceTwo->GetPosition().y);
		}
	}
}

bool PlayerPiece::DropPiece() //Returns false if no piece dropped
{
	bool dropped = false;

	//Piece one drop if possible
	if(m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1))
	{
		m_pieceOne->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1);
		dropped = true;
	}
	else
	{
		m_pieceOne->SetOwner(0);
	}

	//Piece two drop if possible
	if(m_board->IsTileVacant(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1))
	{
		m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1);
		dropped = true;
	}
	else
	{
		m_pieceTwo->SetOwner(0);
	}

	return dropped;
}

void PlayerPiece::DropPieceQuickly()
{
	while(DropPiece())
	{
	}
}

void PlayerPiece::RandomizeNewPiece()
{
	m_pieceOne->Initialize(m_owner);
	m_pieceOne->SetPosition(-1 , -1);
	m_pieceTwo->Initialize(m_owner);
	m_pieceTwo->SetPosition(-1, -1);
}

Piece* PlayerPiece::GetPieceOne()
{
	return m_pieceOne;
}

Piece* PlayerPiece::GetPieceTwo()
{
	return m_pieceTwo;
}

int PlayerPiece::GetColorPieceOne()
{
	return m_pieceOne->GetColor();
}

int PlayerPiece::GetColorPieceTwo()
{
	return m_pieceTwo->GetColor();
}

sf::Vector2i PlayerPiece::GetPositionPieceOne()
{
	return m_pieceOne->GetPosition();
}

sf::Vector2i PlayerPiece::GetPositionPieceTwo()
{
	return m_pieceTwo->GetPosition();
}

int PlayerPiece::GetOwner()
{
	return m_owner;
}

void PlayerPiece::SetColors(int colorOne, int colorTwo)
{
	m_pieceOne->SetColor(colorOne);
	m_pieceTwo->SetColor(colorTwo);
}

void PlayerPiece::SetPositions(int oneX, int oneY, int twoX, int twoY)
{
	m_pieceOne->SetPosition(oneX, oneY);
	m_pieceTwo->SetPosition(twoX, twoY);
}

void PlayerPiece::SetOwner(int owner)
{
	m_owner = owner;
	m_pieceOne->SetOwner(m_owner);
	m_pieceTwo->SetOwner(m_owner);
}

#pragma endregion