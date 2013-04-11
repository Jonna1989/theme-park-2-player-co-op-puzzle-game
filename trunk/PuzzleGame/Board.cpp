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
	CreateBoard();
	m_playerPiece = new PlayerPiece;
	m_playerPiece->Initialize();
	AddPlayer1PieceTo2dVector();
	PrintBoardToConsole();
	GravityClock = new sf::Clock;
	GravityTime = new sf::Time;
}
void Board::Update()
{
	//m_playerPiece->MovePiece(0);
	//AddPlayer1PieceTo2dVector();
	UseTimedFunctions();
	KeyCommand_PrintBoardToConsole();
	Window->clear();
	Window->draw(*m_playerPiece->GetPieceOne()->GetSprite());
	Window->draw(*m_playerPiece->GetPieceTwo()->GetSprite());
	Window->display();

}
void Board::Cleanup()
{
	delete m_Board2dVector;
	delete m_playerPiece;
}

PlayerPiece* Board::GetPlayerPiece()
{
	return m_playerPiece;
}
#pragma endregion
#pragma region Privates
void Board::CreateBoard()
{
	m_Board2dVector = new std::vector< std::vector<int>* >;

	for (unsigned int y = 0; y < BOARD_HEIGHT ; y++) 
	{
		m_Board2dVector->push_back(new std::vector<int>);

		for (unsigned int x = 0; x < BOARD_WIDTH ; x++)  
		{
			(*m_Board2dVector)[y]->push_back(EMPTY_SPACE);
		}
	}
}
void Board::PrintBoardToConsole()
{
	for ( unsigned int y = 0; y < BOARD_HEIGHT; y++ ) 
	{
		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
		{
			std::cout<< std::setw ( 2 ) << (*(*m_Board2dVector)[y])[x] <<' ';
		}
		
		std::cout<<'\n';
	}
	std::cout << "-----------------------------------------------------------" << std::endl;
}
void Board::KeyCommand_PrintBoardToConsole()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		PrintBoardToConsole();
	}
}
void Board::AddPlayer1PieceTo2dVector()
{
	(*(*m_Board2dVector)[m_playerPiece->GetPieceOne()->GetPosition().y])[m_playerPiece->GetPieceOne()->GetPosition().x] = m_playerPiece->GetPieceOne()->GetValue();
	(*(*m_Board2dVector)[m_playerPiece->GetPieceTwo()->GetPosition().y])[m_playerPiece->GetPieceTwo()->GetPosition().x] = m_playerPiece->GetPieceTwo()->GetValue();
}
void Board::Gravity()
{
	for ( unsigned int y = 0; y < BOARD_HEIGHT; y++ ) 
	{
		for ( unsigned int x = 0; x < BOARD_WIDTH; x++ )
		{
			if ((*(*m_Board2dVector)[y])[x] != EMPTY_SPACE)
			{
				if (y+1 >= BOARD_HEIGHT)
				{
					break;
				}
				else if(( *(*m_Board2dVector)[y+1])[x] == EMPTY_SPACE)
				{
					(*(*m_Board2dVector)[y+1])[x] = (*(*m_Board2dVector)[y])[x];
					(*(*m_Board2dVector)[y])[x] = 0;
					y++;					
				}
			}
		}
	}	
}
void Board::UseTimedFunctions()
{
	GravityTime = &GravityClock->getElapsedTime();
	if (GravityTime->asSeconds() >= 2)
	{
		Gravity();
		PrintBoardToConsole();
		GravityClock->restart();
	}
}
#pragma endregion