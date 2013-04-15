#include "InputManager.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
	m_keyboard = new sf::Keyboard;
	m_keyPressedPlayer1 = true;
	m_keyPressedPlayer2 = true;
	m_board = Board::Instance();
}

void InputManager::Initialize(Player* player1)
{
	Initialize();
	m_player1 = player1;
}

void InputManager::Initialize(Player* player1, Player* player2)
{
	Initialize(player1);
	m_player2 = player2;
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
	if((m_keyboard->isKeyPressed(sf::Keyboard::Num4)) && (!m_keyPressedPlayer2))
	{
		m_player2->GetPlayerPiece()->MovePiece(-1);
		m_keyPressedPlayer2 = true;
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::Num6)) && (!m_keyPressedPlayer2))
	{
		m_player2->GetPlayerPiece()->MovePiece(1);
		m_keyPressedPlayer2 = true;	
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::Num7)) && (!m_keyPressedPlayer2))
	{
		m_player2->GetPlayerPiece()->RotatePiece(-1);
		m_keyPressedPlayer2 = true;
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::Num9)) && (!m_keyPressedPlayer2))
	{
		m_player2->GetPlayerPiece()->RotatePiece(1);
		m_keyPressedPlayer2 = true;
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::Num5)) && (!m_keyPressedPlayer2))
	{
		m_player2->GetPlayerPiece()->DropPieceQuickly();
		m_keyPressedPlayer2 = true;
	}

	if((!m_keyboard->isKeyPressed(sf::Keyboard::Num4)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::Num6)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::Num7)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::Num9)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::Num5)))
	{
		m_keyPressedPlayer2 = false;
	}
}