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
	InitializeSprites();
	CreateBoard();

	PrintBoardToConsole();
}

void Board::Update()
{
	Window->clear();
	DrawBoard();
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
	if((0 <= x && x < BOARD_WIDTH) && (0 <= y && y < BOARD_HEIGHT))
	{
		if(GetTile(x, y)->GetContent() == EMPTY_SPACE)
		{
			return true;
		}
	}

	return false;
}

void Board::DropTile(int x, int y)
{
	if(y < BOARD_HEIGHT - 1)
	{
		if(IsTileVacant(x, y + 1))
		{
			GetTile(x, y + 1)->SetContent(GetTile(x, y)->GetContent());
			GetTile(x, y + 1)->SetOwner(GetTile(x, y)->GetOwner());
			GetTile(x, y)->SetContent(0);
			GetTile(x, y)->SetOwner(0);
		}
	}
}

#pragma endregion

#pragma region Privates

void Board::InitializeSprites()
{
	for(int i = 0; i < 5; i++)
	{
		m_sprites.push_back(new sf::Sprite());
	}
	
	m_sprites.at(0)->setTexture(*TextureProvider::Instance()->GetTexture(SHEET_PATH_GREEN));
	m_sprites.at(1)->setTexture(*TextureProvider::Instance()->GetTexture(SHEET_PATH_BLUE));
	m_sprites.at(2)->setTexture(*TextureProvider::Instance()->GetTexture(SHEET_PATH_PURPLE));
	m_sprites.at(3)->setTexture(*TextureProvider::Instance()->GetTexture(SHEET_PATH_RED));
	m_sprites.at(4)->setTexture(*TextureProvider::Instance()->GetTexture(SHEET_PATH_YELLOW));
}

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

void Board::DrawBoard()
{
	int color = 0;

	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			DrawTile(x, y);
		}
	}
}

void Board::DrawTile(int x, int y)
{
	int color = m_board.at(y).at(x).GetContent();

	if(0 < color)
	{
		m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x, m_board.at(y).at(x).GetPositionPixels().y);
		WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(color - 1));
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