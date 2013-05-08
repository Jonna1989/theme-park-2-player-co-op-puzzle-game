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
	m_player1Avatar = new Avatar();
	m_player1Avatar->Initialize("3",100,500);
	m_player2Avatar = new Avatar();
	m_player2Avatar->Initialize("3",1780,500);
	InputManager::Instance()->SetPlayers(m_player1, m_player2);
	Music::Instance()->Initialize(Music::LevelMusic1);
	Music::Instance()->StartMusic();
	m_gravityClock = new sf::Clock();
	m_gravityInterval = 300;
	m_player1Clock = new sf::Clock();
	m_player2Clock = new sf::Clock();
	InputManager::Instance()->SetGravity(m_gravityInterval);
	m_printBoardInterval = new sf::Clock();
	m_increaseClock = new sf::Clock();
	m_increaseInterval = 10000;

	b = Bomb();
	cb = ColorBomb();
}

void Game::Update()
{
	UseTimedFunctions();
	Window->clear();
	Board::Instance()->Update();
	m_player1->Update();
	m_player2->Update();
	m_player1Avatar->Update();
	m_player2Avatar->Update();

	b.Update();
	cb.Update();

	Window->display();	
	KeyCommands();
	Board::Instance()->CheckForGameOver();
}

void Game::Cleanup()
{
	delete m_increaseClock;
	delete m_gravityClock;
	delete m_player1Clock;
	delete m_player2Clock;
	delete m_printBoardInterval;
	m_player1->Cleanup();
	delete m_player1;
	m_player2->Cleanup();
	delete m_player2;
	m_player1Avatar->Cleanup();
	delete m_player1Avatar;
	m_player2Avatar->Cleanup();
	delete m_player2Avatar;
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
	BoardGravity();
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
	if (m_gravityClock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetGravity()/2)
	{
		Board::Instance()->SetBoardHalfStep(TILE_SIZE_Y/2);
	}
	if (m_gravityClock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetGravity())
	{
		Board::Instance()->SetBoardHalfStep(0);
		Gravity();
		m_gravityClock->restart();
		Board::Instance()->CheckForMatch();
	}
	if (m_player1Clock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetPlayer1Gravity()/2 && !Board::Instance()->GetPlayer1HalfStep())
	{
		Board::Instance()->SetPlayer1HalfStep(TILE_SIZE_Y/2);
	}
	if (m_player1Clock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetPlayer1Gravity())
	{
		Board::Instance()->SetPlayer1HalfStep(0);
		m_player1->GetPlayerPiece()->DropPiece();
		m_player1Clock->restart();
	}
	if (m_player2Clock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetPlayer2Gravity()/2 && !Board::Instance()->GetPlayer2HalfStep())
	{
		Board::Instance()->SetPlayer2HalfStep(TILE_SIZE_Y/2);
	}
	if (m_player2Clock->getElapsedTime().asMilliseconds() >= InputManager::Instance()->GetPlayer2Gravity())
	{
		Board::Instance()->SetPlayer2HalfStep(0);
		m_player2->GetPlayerPiece()->DropPiece();
		m_player2Clock->restart();
	}
	if (m_increaseClock->getElapsedTime().asMilliseconds() > m_increaseInterval && m_gravityInterval > 50)
	{
		m_increaseInterval += 2000;
		SetGravityInterval(m_gravityInterval-25);
		InputManager::Instance()->SetGravity(m_gravityInterval);
		m_increaseClock->restart();
	}
}

#pragma endregion

#pragma region KeyCommands

void Game::KeyCommands()
{
	KeyCommand_PrintBoardToConsole();
	KeyCommand_ClearBottomRow();
	KeyCommand_DropBomb();
	KeyCommand_DropColorBomb();
}
void Game::KeyCommand_PrintBoardToConsole()
{
// 	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
// 	{
// 		Board::Instance()->PrintBoardToConsole();
// 	}
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

void Game::KeyCommand_DropBomb()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		b.Initialize();
		b.SetPosition(BOARD_WIDTH / 2, 0);
	}
}

void Game::KeyCommand_DropColorBomb()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		cb.Initialize();
		cb.SetColorToRemove(1);
		cb.SetPosition(BOARD_WIDTH / 2, 0);
	}
}

#pragma endregion