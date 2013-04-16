#include "InputManager.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{
}

InputManager* InputManager::m_instance = 0;

InputManager* InputManager::Instance()
{
	if(m_instance == 0)
	{
		m_instance = new InputManager();
	}

	return m_instance;
}

void InputManager::Initialize()
{
	m_keyboard = new sf::Keyboard;
	m_keyPressedPlayer1 = true;
	m_keyPressedPlayer2 = true;
	m_board = Board::Instance();
}

void InputManager::Update(bool singlePlayer, int state)
{
	switch(state)
	{
	case StateManager::MainMenu: //Menu
		sf::Event event;
		while (Window->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Return)
			{
				StateManager::Instance()->SetState(StateManager::InGame);
				break;
			}
		}
		break;
	case StateManager::InGame: //Game
		CheckPlayer1Input();
		if (!singlePlayer)
		{
			CheckPlayer2Input();
		}
		break;
	}
}
void InputManager::Cleanup()
{
	delete m_keyboard;
}

void InputManager::SetPlayers(Player* player)
{
	m_player1 = player;
}

void InputManager::SetPlayers(Player* player1, Player* player2)
{
	m_player1 = player1;
	m_player2 = player2;
}

void InputManager::CheckPlayer1Input()
{
	while (Window->pollEvent(event1))
	{
		if (event1.type == sf::Event::KeyPressed)
		{
			if (event1.key.code == sf::Keyboard::A && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->MovePiece(-1);
				m_keyPressedPlayer1 = true;
			}
			else if (event1.key.code == sf::Keyboard::D && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer1 = true;
			}

			if (event1.key.code == sf::Keyboard::Q && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->RotatePiece(-1);
				m_keyPressedPlayer1 = true;
			}
			else if (event1.key.code == sf::Keyboard::E && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer1 = true;
			}

			if (event1.key.code == sf::Keyboard::S && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->DropPieceQuickly();
				m_keyPressedPlayer1 = true;
			}

			if ((event1.key.code == sf::Keyboard::Escape))
			{
				Window->close();
			}
		}
		if (event1.type == sf::Event::Closed)
		{
			Window->close();
		}
	}

	if (!m_keyboard->isKeyPressed(sf::Keyboard::A)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::D)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::Q)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::E)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::S))
	{
		m_keyPressedPlayer1 = false;
	}
}

void InputManager::CheckPlayer2Input()
{
	while (Window->pollEvent(event1))
	{
		if (event1.type == sf::Event::KeyPressed)
		{
			if (event1.key.code == sf::Keyboard::H && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->MovePiece(-1);
				m_keyPressedPlayer2 = true;
			}
			else if (event1.key.code == sf::Keyboard::K && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer2 = true;
			}

			if (event1.key.code == sf::Keyboard::Y && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->RotatePiece(-1);
				m_keyPressedPlayer2 = true;
			}
			else if (event1.key.code == sf::Keyboard::I && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer2 = true;
			}

			if (event1.key.code == sf::Keyboard::J && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->DropPieceQuickly();
				m_keyPressedPlayer2 = true;
			}

			if ((event1.key.code == sf::Keyboard::Escape))
			{
				Window->close();
			}
		}
		else
		{
			m_keyPressedPlayer2 = false;
		}
		if (event1.type == sf::Event::Closed)
		{
			Window->close();
		}
	}
	if (!m_keyboard->isKeyPressed(sf::Keyboard::H)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::K)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::Y)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::I)
		&& !m_keyboard->isKeyPressed(sf::Keyboard::J))
	{
		m_keyPressedPlayer2 = false;
	}
}