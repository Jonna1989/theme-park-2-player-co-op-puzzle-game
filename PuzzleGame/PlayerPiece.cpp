#include "PlayerPiece.h"

#pragma region Base

PlayerPiece::PlayerPiece()
{
}


PlayerPiece::~PlayerPiece()
{
}

void PlayerPiece::Initialize(int owner)
{
	m_board = Board::Instance();
	m_owner = owner;

	if(m_owner == 10)
	{
		m_pieceOne = new Piece();
		m_pieceOne->Initialize(m_owner);
		m_spawnPointOne.x = 0;
		m_spawnPointOne.y = 1;
		
		m_pieceTwo = new Piece();
		m_pieceTwo->Initialize(m_owner);
		m_spawnPointTwo.x = 0;
		m_spawnPointTwo.y = 0;
		
		SetPositionToSpawn();
	}
	else if(m_owner == 20)
	{
		m_pieceOne = new Piece();
		m_pieceOne->Initialize(m_owner);
		m_spawnPointOne.x = 5;
		m_spawnPointOne.y = 1;

		m_pieceTwo = new Piece();
		m_pieceTwo->Initialize(m_owner);
		m_spawnPointTwo.x = 5;
		m_spawnPointTwo.y = 0;

		SetPositionToSpawn();
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

#pragma endregion

#pragma region Rotate

void PlayerPiece::RotatePiece(int dir)
{
	if (dir == 1)
	{
		if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //Aligned vertically
		{
			if((m_pieceOne->GetPosition().y > m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x < BOARD_WIDTH - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y))) //Piece one below
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y);
			}
			else if((m_pieceOne->GetPosition().y < m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x > 0)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y))) //Piece one above
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y);
			}
		}
		else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y) //Aligned horizontally
		{
			if((m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y - 1))) //Piece one to the right
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y - 1);
			}
			else if((m_pieceOne->GetPosition().x < m_pieceTwo->GetPosition().x) && (m_pieceOne->GetPosition().y < BOARD_HEIGHT - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1))) //Piece one to the left
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1);
			}
		}
	}
	else if (dir == -1)
	{
		if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //Aligned vertically
		{
			if((m_pieceOne->GetPosition().y > m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x > 0)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y))) //Piece one below
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y);
			}
			else if((m_pieceOne->GetPosition().y < m_pieceTwo->GetPosition().y) && (m_pieceOne->GetPosition().x < BOARD_WIDTH - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y))) //Piece one above
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y);
			}
		}
		else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y) //Aligned horizontally
		{
			if((m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x) && (m_pieceOne->GetPosition().y < BOARD_HEIGHT - 1)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1))) //Piece one to the right
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1);
			}
			else if(m_pieceOne->GetPosition().x < (m_pieceTwo->GetPosition().x)
				&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y - 1))) //Piece one to the left
			{
				m_pieceTwo->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y - 1);
			}
		}
	}
}

#pragma endregion

#pragma region Move

void PlayerPiece::MovePiece(int xDirection)
{
	if (xDirection == 1) //Move right
	{
		if((m_pieceOne->GetPosition().x < BOARD_WIDTH - 1) && (m_pieceTwo->GetPosition().x < BOARD_WIDTH - 1))
		{
			if(m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x) //If piece one is to the right
			{
				if(m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y)) //Adjacent tile is vacant
				{
					if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
					{
						m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 1,m_pieceOne->GetPosition().y);
						m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 1,m_pieceTwo->GetPosition().y);
					}
				}
				else if(m_board->GetTile(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y)->GetOwner() != 0) //Adjacent tile is owned by other player
				{
					if((m_pieceOne->GetPosition().x + 3 < BOARD_WIDTH)
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 2, m_pieceOne->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 3, m_pieceOne->GetPosition().y))) //Skip one column if the next two are vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 3, m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 3, m_pieceTwo->GetPosition().y);
						}
					}
					else if(m_board->GetTile(m_pieceOne->GetPosition().x + 2, m_pieceOne->GetPosition().y)->GetOwner() != 0) //Two adjacent tiles are owned by other player
					{
						if((m_pieceOne->GetPosition().x + 4 < BOARD_WIDTH)
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 3, m_pieceOne->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 4, m_pieceOne->GetPosition().y))) //Skip two columns if next two are vacant and within the board
						{
							if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
							{
								m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 4, m_pieceOne->GetPosition().y);
								m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 4, m_pieceTwo->GetPosition().y);
							}
						}
					}					
				}
			}
			else if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //The pieces are vertically aligned
			{
				if((m_board->IsTileVacant(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y))
					&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 1, m_pieceTwo->GetPosition().y))) //Adjacent tiles are vacant
				{
					if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
					{
						m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 1,m_pieceOne->GetPosition().y);
						m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 1,m_pieceTwo->GetPosition().y);
					}
				}
				else if((m_board->GetTile(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y)->GetOwner() != 0)
					&& (m_board->GetTile(m_pieceTwo->GetPosition().x + 1, m_pieceTwo->GetPosition().y)->GetOwner() != 0)) //Both adjacent tile is owned by other player
				{
					if((m_pieceOne->GetPosition().x + 2 < BOARD_WIDTH) && (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 2, m_pieceOne->GetPosition().y))
					&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 2, m_pieceTwo->GetPosition().y))) //Skip one column if the next one is vacant and within the board 
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 2,m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 2,m_pieceTwo->GetPosition().y);
						}
					}				
				}
				else if(((m_board->GetTile(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y)->GetOwner() != 0)
					&& (m_board->GetTile(m_pieceTwo->GetPosition().x + 1, m_pieceTwo->GetPosition().y)->GetContent() == 0))
					|| ((m_board->GetTile(m_pieceTwo->GetPosition().x + 1, m_pieceTwo->GetPosition().y)->GetOwner() != 0)
					&& (m_board->GetTile(m_pieceOne->GetPosition().x + 1, m_pieceOne->GetPosition().y)->GetContent() == 0))) //One adjacent tile is owned by the other player and the other one is vacant
				{
					if((m_pieceOne->GetPosition().x + 2 < BOARD_WIDTH) && (m_board->IsTileVacant(m_pieceOne->GetPosition().x + 2, m_pieceOne->GetPosition().y))
					&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 2, m_pieceTwo->GetPosition().y))) //Skip one column if the next one is vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 2, m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 2, m_pieceTwo->GetPosition().y);
						}
					}
					else if((m_pieceOne->GetPosition().x + 3 < BOARD_WIDTH) && ((m_board->IsTileVacant(m_pieceOne->GetPosition().x + 3, m_pieceOne->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 3, m_pieceTwo->GetPosition().y)))) //Skip two columns if the next one is vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 3, m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 3, m_pieceTwo->GetPosition().y);
						}
					}					
				}
			}
			else if(m_pieceOne->GetPosition().x < m_pieceTwo->GetPosition().x) //If piece one is to the left
			{
				if(m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 1, m_pieceTwo->GetPosition().y)) //Adjacent tile is vacant
				{
					if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
					{
						m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 1,m_pieceTwo->GetPosition().y);
						m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 1,m_pieceOne->GetPosition().y);
					}
				}
				else if(m_board->GetTile(m_pieceTwo->GetPosition().x + 1, m_pieceTwo->GetPosition().y)->GetOwner() != 0) //Adjacent tile is owned by other player
				{
					if((m_pieceTwo->GetPosition().x + 3 < BOARD_WIDTH)
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 2, m_pieceTwo->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 3, m_pieceTwo->GetPosition().y))) //Skip one column if the next two are vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 3, m_pieceTwo->GetPosition().y);
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 3, m_pieceOne->GetPosition().y);
						}
					}
					else if(m_board->GetTile(m_pieceTwo->GetPosition().x + 2, m_pieceTwo->GetPosition().y)->GetOwner() != 0) //Two columns of tiles are owned by other player
					{
						if((m_pieceTwo->GetPosition().x + 4 < BOARD_WIDTH)
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 3, m_pieceTwo->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x + 4, m_pieceTwo->GetPosition().y))) //Skip two columns if next two are vacant and within the board
						{
							if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
							{
								m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x + 4, m_pieceTwo->GetPosition().y);
								m_pieceOne->SetPosition(m_pieceOne->GetPosition().x + 4, m_pieceOne->GetPosition().y);
							}
						}
					}	
				}
			}
		}
	}
	else if (xDirection == -1) //Move left
	{
		if((m_pieceOne->GetPosition().x > 0) && m_pieceTwo->GetPosition().x > 0)
		{
			if(m_pieceOne->GetPosition().x > m_pieceTwo->GetPosition().x) //If piece one is to the right
			{
				if(m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 1, m_pieceTwo->GetPosition().y)) //Adjacent tile is vacant
				{
					if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
					{
						m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 1,m_pieceTwo->GetPosition().y);
						m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 1,m_pieceOne->GetPosition().y);
					}
				}
				else if(m_board->GetTile(m_pieceTwo->GetPosition().x - 1, m_pieceTwo->GetPosition().y)->GetOwner() != 0) //Adjacent tile is owned by other player
				{
					if((m_pieceTwo->GetPosition().x - 3 >= 0)
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 2, m_pieceTwo->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 3, m_pieceTwo->GetPosition().y))) //Skip one column if the next two are vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 3, m_pieceTwo->GetPosition().y);
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 3, m_pieceOne->GetPosition().y);
						}
					}
					else if(m_board->GetTile(m_pieceTwo->GetPosition().x - 2, m_pieceOne->GetPosition().y)->GetOwner() != 0) //Two adjacent tiles are owned by other player
					{
						if((m_pieceTwo->GetPosition().x - 4 >= 0)
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 3, m_pieceTwo->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 4, m_pieceTwo->GetPosition().y))) //Skip two columns if next two are vacant and within the board
						{
							if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
							{
								m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 4, m_pieceTwo->GetPosition().y);
								m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 4, m_pieceOne->GetPosition().y);
							}
						}
					}					
				}
			}
			else if(m_pieceOne->GetPosition().x == m_pieceTwo->GetPosition().x) //The pieces are vertically aligned
			{
				if((m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y))
					&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 1, m_pieceTwo->GetPosition().y))) //Adjacent tiles are vacant
				{
					if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
					{
						m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 1,m_pieceOne->GetPosition().y);
						m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 1,m_pieceTwo->GetPosition().y);
					}
				}
				else if((m_board->GetTile(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y)->GetOwner() != 0)
					&& (m_board->GetTile(m_pieceTwo->GetPosition().x - 1, m_pieceTwo->GetPosition().y)->GetOwner() != 0)) //Both adjacent tile is owned by other player
				{
					if((m_pieceOne->GetPosition().x - 2 >= 0) && (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 2, m_pieceOne->GetPosition().y))
					&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 2, m_pieceTwo->GetPosition().y))) //Skip one column if the next one is vacant and within the board 
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 2,m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 2,m_pieceTwo->GetPosition().y);
						}
					}				
				}
				else if(((m_board->GetTile(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y)->GetOwner() != 0)
					&& (m_board->GetTile(m_pieceTwo->GetPosition().x - 1, m_pieceTwo->GetPosition().y)->GetContent() == 0))
					|| ((m_board->GetTile(m_pieceTwo->GetPosition().x - 1, m_pieceTwo->GetPosition().y)->GetOwner() != 0)
					&& (m_board->GetTile(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y)->GetContent() == 0))) //One adjacent tile is owned by the other player and the other one is vacant
				{
					if((m_pieceOne->GetPosition().x - 2 >= 0) && (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 2, m_pieceOne->GetPosition().y))
					&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 2, m_pieceTwo->GetPosition().y))) //Skip one column if the next one is vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 2, m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 2, m_pieceTwo->GetPosition().y);
						}
					}
					else if((m_pieceOne->GetPosition().x - 3 >= 0) && ((m_board->IsTileVacant(m_pieceOne->GetPosition().x - 3, m_pieceOne->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceTwo->GetPosition().x - 3, m_pieceTwo->GetPosition().y)))) //Skip two columns if the next one is vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 3, m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 3, m_pieceTwo->GetPosition().y);
						}
					}					
				}
			}
			else if(m_pieceOne->GetPosition().x < m_pieceTwo->GetPosition().x) //If piece one is to the left
			{
				if(m_board->IsTileVacant(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y)) //Adjacent tile is vacant
				{
					if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
					{
						m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 1,m_pieceOne->GetPosition().y);
						m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 1,m_pieceTwo->GetPosition().y);
					}
				}
				else if(m_board->GetTile(m_pieceOne->GetPosition().x - 1, m_pieceOne->GetPosition().y)->GetOwner() != 0) //Adjacent tile is owned by other player
				{
					if((m_pieceOne->GetPosition().x - 3 >= 0)
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 2, m_pieceOne->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 3, m_pieceOne->GetPosition().y))) //Skip one column if the next two are vacant and within the board
					{
						if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
						{
							m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 3, m_pieceOne->GetPosition().y);
							m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 3, m_pieceTwo->GetPosition().y);
						}
					}
					else if(m_board->GetTile(m_pieceOne->GetPosition().x - 2, m_pieceOne->GetPosition().y)->GetOwner() != 0) //Two columns of tiles are owned by other player
					{
						if((m_pieceOne->GetPosition().x - 4 >= 0)
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 3, m_pieceOne->GetPosition().y))
						&& (m_board->IsTileVacant(m_pieceOne->GetPosition().x - 4, m_pieceOne->GetPosition().y))) //Skip two columns if next two are vacant and within the board
						{
							if(m_pieceOne->GetOwner() != 0 && m_pieceTwo->GetOwner() != 0)
							{
								m_pieceOne->SetPosition(m_pieceOne->GetPosition().x - 4, m_pieceOne->GetPosition().y);
								m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x - 4, m_pieceTwo->GetPosition().y);
							}
						}
					}	
				}
			}
		}
	}
}

#pragma endregion

#pragma region Actions

bool PlayerPiece::DropPiece() //Returns false if no piece dropped
{
	bool dropped = false;
	
	bool pieceOneDropped = false;
	bool pieceTwoDropped = false;

	if(m_pieceOne->GetPosition().x != m_pieceTwo->GetPosition().x) //Piece aligned horizontally
	{
		//Piece one drop if possible
		if((0 <= m_pieceOne->GetPosition().y + 1 && m_pieceOne->GetPosition().y + 1 < BOARD_HEIGHT))
		{
			if(m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1))
			{
				m_pieceOne->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1);
				dropped = true;
				pieceOneDropped = true;
			}
			else if(m_board->GetTile(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1)->GetOwner() == 0)
			{
				SetOwner(0);
				SetNewPlayerPieces();
			}
		}
		else if(m_pieceOne->GetPosition().y == BOARD_HEIGHT - 1)
		{
			SetOwner(0);
			SetNewPlayerPieces();
		}

		//Piece two drop if possible
		if((0 <= m_pieceTwo->GetPosition().y + 1 && m_pieceTwo->GetPosition().y + 1 < BOARD_HEIGHT))
		{
			if(m_board->IsTileVacant(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1))
			{
				m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1);
				dropped = true;
				pieceTwoDropped = true;
			}
			else if(m_board->GetTile(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1)->GetOwner() == 0)
			{
				SetOwner(0);
				SetNewPlayerPieces();
			}
		}
		else if(m_pieceTwo->GetPosition().y == BOARD_HEIGHT - 1)
		{
			SetOwner(0);
			SetNewPlayerPieces();
		}
		if ((pieceOneDropped && !pieceTwoDropped) || (!pieceOneDropped && pieceTwoDropped))
		{
			SetOwner(0);
			SetNewPlayerPieces();
		}
	}
	else //Piece aligned vertically
	{
		if((0 <= m_pieceOne->GetPosition().y + 1 && m_pieceOne->GetPosition().y + 1 < BOARD_HEIGHT)
			&& (0 <= m_pieceTwo->GetPosition().y + 1 && m_pieceTwo->GetPosition().y + 1 < BOARD_HEIGHT))
		{
			if(m_pieceTwo->GetPosition().y == m_pieceOne->GetPosition().y - 1) //Piece one lowest
			{
				if(m_board->IsTileVacant(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1))
				{
					m_pieceOne->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1);
					m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1);
					dropped = true;
				}
				else if(m_board->GetTile(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1)->GetOwner() == 0)
				{
					SetOwner(0);
					SetNewPlayerPieces();
				}
				else if(m_pieceOne->GetPosition().y == BOARD_HEIGHT - 1)
				{
					SetOwner(0);
					SetNewPlayerPieces();
				}
			}
			else if(m_pieceOne->GetPosition().y == m_pieceTwo->GetPosition().y - 1) //Piece two lowest
			{
				if(m_board->IsTileVacant(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1))
				{
					m_pieceTwo->SetPosition(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1);
					m_pieceOne->SetPosition(m_pieceOne->GetPosition().x, m_pieceOne->GetPosition().y + 1);
					dropped = true;
				}
				else if(m_board->GetTile(m_pieceTwo->GetPosition().x, m_pieceTwo->GetPosition().y + 1)->GetOwner() == 0)
				{
					SetOwner(0);
					SetNewPlayerPieces();
				}
				else if(m_pieceTwo->GetPosition().y == BOARD_HEIGHT - 1)
				{
					SetOwner(0);
					SetNewPlayerPieces();
				}
			}
		}
		else if((m_pieceOne->GetPosition().y == BOARD_HEIGHT - 1) || (m_pieceTwo->GetPosition().y == BOARD_HEIGHT - 1))
		{
			SetOwner(0);
			SetNewPlayerPieces();
		}
	}

	return dropped;
}

void PlayerPiece::DropPieceQuickly()
{
	bool pieceDropped = true;
	
	do
	{
		pieceDropped = DropPiece();
	}
	while(pieceDropped);
}

void PlayerPiece::RandomizeNewPiece()
{
	m_pieceOne->RandomizeColor();
	m_pieceTwo->RandomizeColor();
	SetPositionToSpawn();
}

#pragma endregion

#pragma region Getters

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

sf::Vector2i PlayerPiece::GetSpawnPointOne()
{
	return m_spawnPointOne;
}

sf::Vector2i PlayerPiece::GetSpawnPointTwo()
{
	return m_spawnPointTwo;
}

#pragma endregion

#pragma region Setters

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

void PlayerPiece::SetPositionToSpawn()
{
	SetPositions(m_spawnPointOne.x, m_spawnPointOne.y, m_spawnPointTwo.x, m_spawnPointTwo.y);
}

void PlayerPiece::SetSpawnPointOne(int x, int y)
{
	m_spawnPointOne.x = x;
	m_spawnPointOne.y = y;
}

void PlayerPiece::SetSpawnPointTwo(int x, int y)
{
	m_spawnPointTwo.x = x;
	m_spawnPointTwo.y = y;
}

void PlayerPiece::SetNewPlayerPieces()
{
	int oneValue = Board::Instance()->GetTile(m_pieceOne->GetPosition().x,m_pieceOne->GetPosition().y)->GetContent();
	int twoValue = Board::Instance()->GetTile(m_pieceTwo->GetPosition().x,m_pieceTwo->GetPosition().y)->GetContent();
	int onePosX = m_pieceOne->GetPosition().x;
	int onePosY = m_pieceOne->GetPosition().y;
	int twoPosX = m_pieceTwo->GetPosition().x;
	int twoPosY = m_pieceTwo->GetPosition().y;
	RandomizeNewPiece();
	SetOwner(10);
	Board::Instance()->GetTile(onePosX,onePosY)->SetContent(oneValue);
	Board::Instance()->GetTile(twoPosX,twoPosY)->SetContent(twoValue);
}

#pragma endregion