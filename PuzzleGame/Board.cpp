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
	VectorFill.x = BLUE_SPACE;
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
	//m_playerPiece->MovePiece(0);
	//AddPlayer1PieceTo2dVector();
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
	delete m_playerPiece;
	delete GravityClock;
	delete GravityTime;
}

PlayerPiece* Board::GetPlayerPiece()
{
	return m_playerPiece;
}

// std::vector< std::vector<sf::Vector2i>* >* Board::GetVector()
// {
// 	return m_Board2dVector;
// }
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
			std::cout<< std::setw ( 2 ) << GetBoardVector(y,x) <<' ';
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
			SetBoardVector(BOARD_HEIGHT-1,x,EMPTY_SPACE);
		}
	}
}
#pragma endregion
void Board::AddPlayer1PieceTo2dVector()
{
	(*(*m_Board2dVector)[m_playerPiece->GetPieceOne()->GetPosition().y/100])[m_playerPiece->GetPieceOne()->GetPosition().x].x = m_playerPiece->GetPieceOne()->GetValue();
	(*(*m_Board2dVector)[m_playerPiece->GetPieceTwo()->GetPosition().y/100])[m_playerPiece->GetPieceTwo()->GetPosition().x].x = m_playerPiece->GetPieceTwo()->GetValue();
}
void Board::Gravity()
{
// 	for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
// 	{
// 		for (unsigned int y = 9; y >= 1; y-- ) 
// 		{
// 			if ((GetBoardVector(y+1,x) == EMPTY_SPACE) || (y = 9) )
// 			{
// 				int temp = 0;
// 				temp = GetBoardVector(y,x);
// 				SetBoardVector(y,x,EMPTY_SPACE);
// 				SetBoardVector(y+1,x,temp);
// 			}
// 		}
// 	}
// 	
// 	for ( unsigned int y = 0; y < BOARD_HEIGHT; y++ ) 
// 	{
// 		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
// 		{
// 			if (GetBoardVector(y,x) != EMPTY_SPACE)
// 			{
// 				if (y+1 >= BOARD_HEIGHT)
// 				{
// 					break;
// 				}
// 				else if(GetBoardVector(y+1,x) == EMPTY_SPACE)
// 				{
// 					SetBoardVector(y+1,x,GetBoardVector(y,x));
// 					if (y-1 < 0)
// 					{
// 						break;
// 					}
// 					else if (GetBoardVector(y-1,x) != EMPTY_SPACE)
// 					{
// 						SetBoardVector(y,x,GetBoardVector(y-1,x));
// 						SetBoardVector(y-1,x,EMPTY_SPACE); 
// 					}
// 					y++;					
// 				}
// 			}
// 		}
// 	}
	for ( unsigned int y = BOARD_HEIGHT -1; y >= 1; y-- ) 
	{
		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
		{
			if ( (GetBoardVector(y,x) == EMPTY_SPACE) && GetBoardVector(y-1,x) )
			{
				int temp = 0;
				temp = GetBoardVector(y-1,x);
				SetBoardVector(y-1,x,EMPTY_SPACE);
				SetBoardVector(y,x,temp); 
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
int Board::GetBoardVector(int y, int x)
{
	return (*(*m_Board2dVector)[y])[x].x;
}
void Board::SetBoardVector(int y, int x, int newValue)
{
	(*(*m_Board2dVector)[y])[x].x = newValue;
}
#pragma endregion