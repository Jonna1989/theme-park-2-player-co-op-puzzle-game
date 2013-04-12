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
	m_playerPiece->Initialize();
	AddPlayer1PieceTo2dVector();
	PrintBoardToConsole();
	GravityClock = new sf::Clock;
	GravityTime = new sf::Time;
	GravityInterval = 2000;

}
void Board::Update()
{
	UseTimedFunctions();
	KeyCommands();
	Window->clear();
	Window->draw(*m_playerPiece->GetPieceOne()->GetSprite());
	Window->draw(*m_playerPiece->GetPieceTwo()->GetSprite());
	Window->display();
}
void Board::Cleanup()
{
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
	for ( unsigned int y = 0; y < BOARD_HEIGHT; y++ ) 
	{
		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
		{
			std::cout<< std::setw ( 2 ) << GetBoardVectorX(y,x) <<' ';
		}
		
		std::cout<<'\n';
	}
	std::cout << "---------------------------------------------" << std::endl;
}
#pragma endregion
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
		}
	}
}
#pragma endregion
void Board::AddPlayer1PieceTo2dVector()
{
	SetBoardVectorX(m_playerPiece->GetPieceOne()->GetPosition().y,m_playerPiece->GetPieceOne()->GetPosition().x,m_playerPiece->GetPieceOne()->GetValue());
	SetBoardVectorX(m_playerPiece->GetPieceTwo()->GetPosition().y,m_playerPiece->GetPieceTwo()->GetPosition().x,m_playerPiece->GetPieceTwo()->GetValue());
	SetBoardVectorY(m_playerPiece->GetPieceOne()->GetPosition().y,m_playerPiece->GetPieceOne()->GetPosition().x,PLAYER_ONE);
	SetBoardVectorY(m_playerPiece->GetPieceTwo()->GetPosition().y,m_playerPiece->GetPieceTwo()->GetPosition().x,PLAYER_ONE);
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
				tempY = GetBoardVectorX(y-1,x);
				SetBoardVectorY(y-1,x,PASSIVE);
				SetBoardVectorY(y,x,tempY);
				m_playerPiece->GetPieceOne()->SetPosition(tempX,tempY);
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
#pragma endregion