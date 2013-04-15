#include "Board.h"

#pragma region Base
Board::Board()
{
}

Board::~Board()
{
}

Board* Board::m_instance = 0;

Board* Board::Instance()
{
	if(m_instance == 0)
	{
		m_instance = new Board();
	}

	return m_instance;
}

void Board::Initialize()
{
	CreateBoard();

	PrintBoardToConsole();
}

void Board::Update()
{
	Window->clear();

	Window->display();
}

void Board::Cleanup()
{
	delete m_instance;
}

#pragma endregion

#pragma region Getters

std::vector<std::vector<Tile>> Board::GetBoard()
{
	return m_board;
}

Tile* Board::GetTile(int x, int y)
{
	return &m_board.at(y).at(x);
}

int Board::GetColor(int x, int y)
{
	return m_board.at(y).at(x).GetContent();
}

int Board::GetOwner(int x, int y)
{
	return m_board.at(y).at(x).GetOwner();
}

#pragma endregion

#pragma region Setters

void Board::SetColor(int x, int y, int color)
{
	m_board.at(y).at(x).SetContent(color);
}

void Board::SetOwner(int x, int y, int owner)
{
	m_board.at(y).at(x).SetOwner(owner);
}

#pragma endregion

#pragma region Publics

bool Board::IsTileVacant(int x, int y)
{
	if(m_board.at(y).at(x).GetContent() == EMPTY_SPACE)
	{
		return true;
	}

	return false;
}

#pragma endregion

#pragma region Privates

void Board::CreateBoard()
{
	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		m_board.push_back(std::vector<Tile>());

		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			m_board.at(y).push_back(Tile());
			m_board.at(y).at(x).Initialize(TILE_SIZE_X, TILE_SIZE_Y, x, y);
		}
	}
}

void Board::PrintBoardToConsole()
{
	std::system("cls");
	for(int y = 0; y < BOARD_HEIGHT; y++) 
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			std::cout<< std::setw (2) << m_board.at(y).at(x).GetContent() <<' ';
		}
		
		std::cout<<'\n';
	}
}

#pragma endregion