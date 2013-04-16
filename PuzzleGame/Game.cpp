#include "Game.h"

#pragma region Base

Game::Game()
{
}


Game::~Game()
{
}

void Game::Initialize()
{
	Board::Instance()->Initialize();
	m_player1 = new Player();
	m_player1->Initialize(10);
	m_player2 = new Player();
	m_player2->Initialize(20);
	InputManager::Instance()->SetPlayers(m_player1, m_player2);
	m_gravityClock = new sf::Clock;
	m_gravityInterval = 2000;
}

void Game::Update()
{
	UseTimedFunctions();
	Board::Instance()->Update();	
	KeyCommands();
}

void Game::Cleanup()
{
	delete m_gravityClock;
	Board::Instance()->Cleanup();
}

#pragma endregion

#pragma region Getters

int Game::GetGravityInterval()
{
	return m_gravityInterval;
}

#pragma endregion

#pragma region Setters

void Game::SetGravityInterval(int milliSeconds)
{
	m_gravityInterval = milliSeconds;
}

#pragma region Privates

void Game::Gravity()
{
	if((!m_player1->GetPlayerPiece()->DropPiece()) || (!m_player2->GetPlayerPiece()->DropPiece()))
	{
		BoardGravity();
	}
}

void Game::BoardGravity()
{
	for(int y = BOARD_HEIGHT - 2; y >= 0; y--) //Can't move the last row any further down so start checking the row above
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			Board::Instance()->DropTile(x, y);
		}
	}
}

void Game::UseTimedFunctions()
{
	if (m_gravityClock->getElapsedTime().asMilliseconds() >= m_gravityInterval)
	{
		Gravity();
		Board::Instance()->PrintBoardToConsole();
		m_gravityClock->restart();
	}
}

#pragma endregion

#pragma region KeyCommands

void Game::KeyCommands()
{
	KeyCommand_DropNewPiece();
	KeyCommand_PrintBoardToConsole();
	KeyCommand_ClearBottomRow();
}
void Game::KeyCommand_PrintBoardToConsole()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		Board::Instance()->PrintBoardToConsole();
	}
}
void Game::KeyCommand_DropNewPiece()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		m_player1->GetPlayerPiece()->DropPieceQuickly();
		m_player1->GetPlayerPiece()->RandomizeNewPiece();
	}
}
void Game::KeyCommand_ClearBottomRow()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		for (int x = 0; x < (int)BOARD_WIDTH; x++)
		{
			Board::Instance()->GetTile(x, BOARD_HEIGHT - 1)->ClearTile();
		}
	}
}

#pragma endregion