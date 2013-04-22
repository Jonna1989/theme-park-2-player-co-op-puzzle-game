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
	Music::Instance()->Initialize(Music::LevelMusic1);
	Music::Instance()->StartMusic();
	m_gravityClock = new sf::Clock();
	m_gravityInterval = 300;
	m_player1Clock = new sf::Clock();
	m_player2Clock = new sf::Clock();
	InputManager::Instance()->SetGravity(m_gravityInterval);
	m_printBoardInterval = new sf::Clock();
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
	delete m_player1Clock;
	delete m_player2Clock;
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
	//if((!m_player1->GetPlayerPiece()->DropPiece()) || (!m_player2->GetPlayerPiece()->DropPiece()))
	//{
		BoardGravity();
	//}
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
	if (m_gravityClock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetGravity())
	{
		Gravity();
		m_gravityClock->restart();
		Board::Instance()->CheckForMatch();
	}
	if (m_player1Clock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetPlayer1Gravity())
	{
		m_player1->GetPlayerPiece()->DropPiece();
		m_player1Clock->restart();
	}
	if (m_player2Clock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetPlayer2Gravity())
	{
		m_player2->GetPlayerPiece()->DropPiece();
		m_player2Clock->restart();
	}
	if (m_printBoardInterval->getElapsedTime().asSeconds() >= 5)
	{
		Board::Instance()->PrintBoardToConsole();
		m_printBoardInterval->restart();
	}
}

#pragma endregion

#pragma region KeyCommands

void Game::KeyCommands()
{
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