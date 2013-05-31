#include "Game.h"

#pragma region Base

Game::Game()
{
	m_player1 = nullptr;
	m_player2 = nullptr;
	m_player1Avatar = nullptr;
	m_player2Avatar = nullptr;
	m_gravityClock = nullptr;
	m_gravityInterval = NULL;
	m_increaseClock = nullptr;
	m_player1Clock = nullptr;
	m_player2Clock = nullptr;
	m_printBoardInterval = nullptr;
	m_speedUpSprite = nullptr;
	m_speedUpSpriteAlpha = NULL;
	m_increaseInterval = NULL;
	b = nullptr;
	cb = nullptr;
	t = nullptr;
	keyPressedColorBomb = NULL;
	keyPressedBomb = NULL;
	keyPressedThorn = NULL;
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
	m_player1Avatar->Initialize("lily_idle",50,400, sf::Vector2f(1280/4,523), sf::Vector2i(0,0), 4, 6, 8,rand () % (10 - 5) + 5, 1);
	m_player2Avatar = new Avatar();
	m_player2Avatar->Initialize("rose_idle",1550,400, sf::Vector2f(1108/4,534), sf::Vector2i(0,0), 4, 6, 8,rand () % (10 - 5) + 5, 2);
	InputManager::Instance()->SetPlayers(m_player1, m_player2);
	m_gravityClock = new sf::Clock();
	m_gravityInterval = 1500;
	m_player1Clock = new sf::Clock();
	m_player2Clock = new sf::Clock();
	InputManager::Instance()->SetGravity(m_gravityInterval);
	m_printBoardInterval = new sf::Clock();
	m_increaseClock = new sf::Clock();
	m_increaseInterval = 10000;

	CreateSprite(m_speedUpSprite,"Assets/GraphicalAssets/Speedup/speed.png");
	m_speedUpSprite->setPosition(((Window->getSize().x)-(m_speedUpSprite->getGlobalBounds().width))/2,400);
	m_speedUpSpriteAlpha = 0.0f;

	b = nullptr;
	cb = nullptr;
	t = nullptr;
	keyPressedBomb = false;
	keyPressedColorBomb = false;
	keyPressedThorn = false;
}

void Game::Update()
{
	UseTimedFunctions();
	Window->clear();
	Board::Instance()->Update();
	m_player1Avatar->Update();
	m_player2Avatar->Update();
	m_player1->Update();
	m_player2->Update();

	if(b != nullptr && !b->HasActivated())
	{
		b->Update();
	}

	if(cb != nullptr && !cb->HasActivated())
	{
		cb->Update();
	}

	if(t != nullptr && !t->HasActivated())
	{
		t->Update();
	}

	m_speedUpSprite->setColor(sf::Color(255,255,225,(sf::Uint8)m_speedUpSpriteAlpha));

	if (m_speedUpSpriteAlpha > 5)
	{
		Window->draw(*m_speedUpSprite);
		m_speedUpSpriteAlpha -= 100*DeltaTime;
	}

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
	Clean(m_speedUpSprite);
	
	if(b != nullptr)
	{
		b->Cleanup();
		delete b;
	}

	if(cb != nullptr)
	{
		cb->Cleanup();
		delete cb;
	}

	if(t != nullptr)
	{
		t->Cleanup();
		delete t;
	}
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
		m_increaseInterval += 4000;
		SetGravityInterval(m_gravityInterval-25);
		InputManager::Instance()->SetGravity(m_gravityInterval);
		m_speedUpSpriteAlpha = 255;
		Soundeffects::Instance()->PlayRandomSoundInCategory(Soundeffects::SPEEDUPSOUND,0,4);
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
	KeyCommand_DropThorn();
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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::V) && !keyPressedBomb)
	{
		keyPressedBomb = true;

		if(b == nullptr)
		{
			b = new Bomb();
			b->Initialize();
			b->SetPosition(BOARD_WIDTH / 2, 2);
		}
		else if(b->HasActivated())
		{
			b->Cleanup();
			delete b;
			b = nullptr;
		}		
	}

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		keyPressedBomb = false;
	}
}

void Game::KeyCommand_DropColorBomb()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !keyPressedColorBomb)
	{
		keyPressedColorBomb = true;

		if(cb == nullptr)
		{
			cb = new ColorBomb();
			cb->Initialize();
			int color = (rand() % 7) + 1;
			cb->SetColorToRemove(color);
			cb->SetPosition(BOARD_WIDTH / 2, 2);
		}
		else if(cb->HasActivated())
		{
			cb->Cleanup();
			delete cb;
			cb = nullptr;
		}
	}

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		keyPressedColorBomb = false;
	}
}

void Game::KeyCommand_DropThorn()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !keyPressedThorn)
	{
		keyPressedThorn = true;

		if(t == nullptr)
		{
			t = new Thorn();
			t->Initialize();
			t->SetPosition(BOARD_WIDTH / 2, 2);
		}
		else if(t->HasActivated())
		{
			t->Cleanup();
			delete t;
			t = nullptr;
		}
	}

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		keyPressedThorn = false;
	}
}

#pragma endregion