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
	PrintBoardToConsole();
	m_playerPiece = new PlayerPiece;
	m_playerPiece->Initialize();
}
void Board::Update()
{

}
void Board::Cleanup()
{
	delete m_Board2dVector;
	delete m_playerPiece;
}
#pragma endregion
#pragma region Privates
void Board::CreateBoard()
{
	m_Board2dVector = new std::vector< std::vector<int>* >;

	for (unsigned int i = 0; i < BOARD_HEIGHT ; i++) 
	{
		m_Board2dVector->push_back(new std::vector<int>);

		for (unsigned int j = 0; j < BOARD_WIDTH ; j++)  
		{
			(*m_Board2dVector)[i]->push_back(EMPTY_SPACE);
		}
	}
}
void Board::PrintBoardToConsole()
{
	for ( unsigned int i = 0; i < BOARD_HEIGHT; i++ ) 
	{
		for ( unsigned int j = 0; j < BOARD_WIDTH; j++ )
		{
			std::cout<< std::setw ( 2 ) << (*(*m_Board2dVector)[i])[j] <<' ';
		}
		
		std::cout<<'\n';
	}
	std::cout << "-----------------------------------------------------------" << std::endl;
}
PlayerPiece* Board::ReturnPlayerPiece()
{

}
void PlacePiece()
{

}
#pragma endregion