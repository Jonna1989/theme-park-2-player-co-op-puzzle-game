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
		CheckPlayer2Input();
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
	do
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::A && !m_keyPressedPlayer1)
			{
				std::cout << "A" << std::endl;
				m_player1->GetPlayerPiece()->MovePiece(-1);
				m_keyPressedPlayer1 = true;
			}
			else if (event.key.code == sf::Keyboard::D && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer1 = true;
			}

			if (event.key.code == sf::Keyboard::Q && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->RotatePiece(-1);
				m_keyPressedPlayer1 = true;
			}
			else if (event.key.code == sf::Keyboard::E && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer1 = true;
			}

			if (event.key.code == sf::Keyboard::S && !m_keyPressedPlayer1)
			{
				m_player1->GetPlayerPiece()->DropPieceQuickly();
				m_keyPressedPlayer1 = true;
			}

			if ((event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed))
			{
				Window->close();
			}
		}
		else
		{
			m_keyPressedPlayer1 = false;
		}
	} while (Window->pollEvent(event));
}

void InputManager::CheckPlayer2Input()
{
	do
	{
		if (event2.type == sf::Event::KeyPressed)
		{
			if (event2.key.code == sf::Keyboard::Num4 && !m_keyPressedPlayer2)
			{
				std::cout << "A" << std::endl;
				m_player2->GetPlayerPiece()->MovePiece(-1);
				m_keyPressedPlayer2 = true;
			}
			else if (event2.key.code == sf::Keyboard::Num6 && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer2 = true;
			}

			if (event2.key.code == sf::Keyboard::Num7 && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->RotatePiece(-1);
				m_keyPressedPlayer2 = true;
			}
			else if (event2.key.code == sf::Keyboard::Num9 && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->MovePiece(1);
				m_keyPressedPlayer2 = true;
			}

			if (event2.key.code == sf::Keyboard::Num5 && !m_keyPressedPlayer2)
			{
				m_player2->GetPlayerPiece()->DropPieceQuickly();
				m_keyPressedPlayer2 = true;
			}

			if ((event2.key.code == sf::Keyboard::Escape) || (event2.type == sf::Event::Closed))
			{
				Window->close();
			}
		}
		else
		{
			m_keyPressedPlayer2 = false;
		}
	} while (Window->pollEvent(event2));
	
}