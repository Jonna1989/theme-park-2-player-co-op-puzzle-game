#include "Board.h"

#pragma region Base
Board::Board()
{
}


Board::~Board()
{
}
#pragma endregion
#pragma region Publics
void Board::Initialize()
{
	VectorFill.x = EMPTY_SPACE;
	VectorFill.y = PASSIVE;
	CreateBoard();
	m_playerPiece = new PlayerPiece;
	m_playerPiece->Initialize(BOARD_HEIGHT, BOARD_WIDTH);
	AddPlayer1PieceTo2dVector();
//	PrintBoardToConsole();
	GravityClock = new sf::Clock;
	GravityTime = new sf::Time;
	GravityInterval = 2000;
	LoadTexture(m_green,"Assets/GraphicalAssets/TempArt/ball1.png");
	LoadTexture(m_blue,"Assets/GraphicalAssets/TempArt/ball2.png");
	LoadTexture(m_purple,"Assets/GraphicalAssets/TempArt/ball3.png");
	LoadTexture(m_red,"Assets/GraphicalAssets/TempArt/ball4.png");
	LoadTexture(m_yellow,"Assets/GraphicalAssets/TempArt/ball5.png");
	m_pieceSprite = new sf::Sprite;
}
void Board::Update()
{
	UseTimedFunctions();
	UpdatePlayer1VectorPos();
	//UpdatePlayer1PlayerPiece();
	KeyCommands();
	Window->clear();
	SpaceDrawer();
	Window->display();
}
void Board::Cleanup()
{
	for(unsigned int i = 0; i < m_Board2dVector->size(); i++)
	{
		delete m_Board2dVector->at(i);	
	}

	delete m_Board2dVector;
	m_playerPiece->Cleanup();
	delete m_playerPiece;
	delete GravityClock;
//	Memory Leak "Fix"
//	delete GravityTime; _BLOCK_TYPE_IS_VALID(pHead->nBlockUse)
}
int Board::GetBoardVectorX(int y, int x)
{
	return (*(*m_Board2dVector)[y])[x].x;
}
int Board::GetBoardVectorY(int y, int x)
{
	return (*(*m_Board2dVector)[y])[x].y;
}
PlayerPiece* Board::GetPlayerPiece()
{
	return m_playerPiece;
}

bool Board::IsTileVacant(int x, int y)
{
	if(GetBoardVectorX(y, x) == EMPTY_SPACE)
	{
		return true;
	}

	return false;
}
#pragma endregion
#pragma region Privates
void Board::CreateBoard()
{
	m_Board2dVector = new std::vector< std::vector<sf::Vector2i>* >;

	for (unsigned int y = 0; y < BOARD_HEIGHT ; y++) 
	{
		m_Board2dVector->push_back(new std::vector<sf::Vector2i>);

		for (unsigned int x = 0; x < BOARD_WIDTH ; x++)  
		{
			(*m_Board2dVector)[y]->push_back(VectorFill);
		}
	}
}
#pragma region PrintBoardToConsole
void Board::PrintBoardToConsole()
{
	std::system("cls");
	for ( unsigned int y = 0; y < BOARD_HEIGHT; y++ ) 
	{
		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
		{
			std::cout<< std::setw ( 2 ) << GetBoardVectorX(y,x) <<' ';
		}
		
		std::cout<<'\n';
	}
	
}
#pragma endregion
void Board::PrintPlayerOnePlayerPiecePositionsToConsole()
{
	for (unsigned int y = 0; y < BOARD_HEIGHT ; y++)
	{
		for (unsigned int x = 0; x < BOARD_WIDTH ; x++)
		{
			if (GetBoardVectorY(y,x) == PLAYER_ONE_PIECE_ONE)
			{
				std::cout << "Piece One X:"<< m_playerPiece->GetPieceOne()->GetPosition().x <<" Y:"<< m_playerPiece->GetPieceOne()->GetPosition().y <<" = "<<GetBoardVectorX(y,x) << std::endl;
			}
			else if (GetBoardVectorY(y,x) == PLAYER_ONE_PIECE_TWO)
			{
				std::cout << "Piece Two X:"<<m_playerPiece->GetPieceTwo()->GetPosition().x <<" Y:"<< m_playerPiece->GetPieceTwo()->GetPosition().y<<" = "<< GetBoardVectorX(y,x) << std::endl;
			}
		}
	}
}
#pragma region KeyCommands
void Board::KeyCommands()
{
	KeyCommand_DropNewPiece();
	KeyCommand_PrintBoardToConsole();
	KeyCommand_ClearBottomRow();
}
void Board::KeyCommand_PrintBoardToConsole()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		PrintBoardToConsole();
	}
}
void Board::KeyCommand_DropNewPiece()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		AddPlayer1PieceTo2dVector();
	}
}
void Board::KeyCommand_ClearBottomRow()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		for (int x = 0; x < (int)BOARD_WIDTH; x++)
		{
			SetBoardVectorX(BOARD_HEIGHT-1,x,EMPTY_SPACE);
			SetBoardVectorY(BOARD_HEIGHT-1,x,PASSIVE);
		}
	}
}
#pragma endregion
void Board::AddPlayer1PieceTo2dVector()
{
	SetBoardVectorX(m_playerPiece->GetPieceOne()->GetPosition().y,m_playerPiece->GetPieceOne()->GetPosition().x,m_playerPiece->GetPieceOne()->GetValue());
	SetBoardVectorX(m_playerPiece->GetPieceTwo()->GetPosition().y,m_playerPiece->GetPieceTwo()->GetPosition().x,m_playerPiece->GetPieceTwo()->GetValue());
	SetBoardVectorY(m_playerPiece->GetPieceOne()->GetPosition().y,m_playerPiece->GetPieceOne()->GetPosition().x,PLAYER_ONE_PIECE_ONE);
	SetBoardVectorY(m_playerPiece->GetPieceTwo()->GetPosition().y,m_playerPiece->GetPieceTwo()->GetPosition().x,PLAYER_ONE_PIECE_TWO);
}
void Board::Gravity()
{
	for ( unsigned int y = BOARD_HEIGHT -1; y >= 1; y-- ) 
	{
		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
		{
			if ( (GetBoardVectorX(y,x) == EMPTY_SPACE) && GetBoardVectorX(y-1,x) )
			{
				int tempX = 0;
				tempX = GetBoardVectorX(y-1,x);
				SetBoardVectorX(y-1,x,EMPTY_SPACE);
				SetBoardVectorX(y,x,tempX); 
				int tempY = 0;
				tempY = GetBoardVectorY(y-1,x);
				SetBoardVectorY(y-1,x,PASSIVE);
				SetBoardVectorY(y,x,tempY);

			}
		}
	}
}
void Board::UpdatePlayer1PlayerPiece()
{
	for (unsigned int y = 0; y < BOARD_HEIGHT ; y++)
	{
		for (unsigned int x = 0; x < BOARD_WIDTH ; x++)
		{
			if (GetBoardVectorY(y,x) == PLAYER_ONE_PIECE_ONE)
			{
				m_playerPiece->GetPieceOne()->SetPosition(m_playerPiece->GetPieceOne()->GetPosition().x,y);
			}
			else if (GetBoardVectorY(y,x) == PLAYER_ONE_PIECE_TWO)
			{
				m_playerPiece->GetPieceTwo()->SetPosition(m_playerPiece->GetPieceTwo()->GetPosition().x,y);
			}
		}
	}
}
void Board::UpdatePlayer1VectorPos()
{
	for (unsigned int y = 0; y < BOARD_HEIGHT ; y++)
	{
		for (unsigned int x = 0; x < BOARD_WIDTH ; x++)
		{
			if ( (GetBoardVectorY(y,x) == PLAYER_ONE_PIECE_ONE) && (m_playerPiece->GetPieceOne()->GetPosition().x != x))
			{
				int temp = 0;
				temp = GetBoardVectorY(y,x);
				SetBoardVectorY(y,x,PASSIVE);
				SetBoardVectorY(y,m_playerPiece->GetPieceOne()->GetPosition().x,temp);
				temp = GetBoardVectorX(y,x);
				SetBoardVectorX(y,x,EMPTY_SPACE);
				SetBoardVectorX(y,m_playerPiece->GetPieceOne()->GetPosition().x,temp);
			}
			else if ( (GetBoardVectorY(y,x) == PLAYER_ONE_PIECE_TWO) && (m_playerPiece->GetPieceTwo()->GetPosition().x != x))
			{
				int temp = 0;
				temp = GetBoardVectorY(y,x);
				SetBoardVectorY(y,x,PASSIVE);
				SetBoardVectorY(y,m_playerPiece->GetPieceTwo()->GetPosition().x,temp);
				temp = GetBoardVectorX(y,x);
				SetBoardVectorX(y,x,EMPTY_SPACE);
				SetBoardVectorX(y,m_playerPiece->GetPieceTwo()->GetPosition().x,temp);
			}
		}
	}
}
void Board::UseTimedFunctions()
{
	GravityTime = &GravityClock->getElapsedTime();
	if (GravityTime->asMilliseconds() >= GravityInterval)
	{
		Gravity();
		PrintBoardToConsole();
		PrintPlayerOnePlayerPiecePositionsToConsole();
		GravityClock->restart();
	}
}
void Board::SetBoardVectorX(int y, int x, int newValue)
{
	(*(*m_Board2dVector)[y])[x].x = newValue;
}
void Board::SetBoardVectorY(int y, int x, int newValue)
{
	(*(*m_Board2dVector)[y])[x].y = newValue;
}
void Board::SpaceDrawer()
{
	for (unsigned int y = 0; y < BOARD_HEIGHT ; y++)
	{
		for (unsigned int x = 0; x < BOARD_WIDTH ; x++)
		{
			if (GetBoardVectorX(y,x) == GREEN_SPACE)
			{
				m_pieceSprite->setPosition((float)x*1920/BOARD_WIDTH,(float)y*1080/BOARD_HEIGHT);
				m_pieceSprite->setTexture(*m_green);
			}
			else if (GetBoardVectorX(y,x) == BLUE_SPACE)
			{
				m_pieceSprite->setPosition((float)x*1920/BOARD_WIDTH,(float)y*1080/BOARD_HEIGHT);
				m_pieceSprite->setTexture(*m_blue);
			}
			else if (GetBoardVectorX(y,x) == PURPLE_SPACE)
			{
				m_pieceSprite->setPosition((float)x*1920/BOARD_WIDTH,(float)y*1080/BOARD_HEIGHT);
				m_pieceSprite->setTexture(*m_purple);
			}
			else if (GetBoardVectorX(y,x) == RED_SPACE)
			{
				m_pieceSprite->setPosition((float)x*1920/BOARD_WIDTH,(float)y*1080/BOARD_HEIGHT);
				m_pieceSprite->setTexture(*m_red);
			}
			else if (GetBoardVectorX(y,x) == YELLOW_SPACE)
			{
				m_pieceSprite->setPosition((float)x*1920/BOARD_WIDTH,(float)y*1080/BOARD_HEIGHT);
				m_pieceSprite->setTexture(*m_yellow);
			}
			if (GetBoardVectorX(y,x) != EMPTY_SPACE)
			{
				Window->draw(*m_pieceSprite);
			}
		}
	}
}
#pragma endregion