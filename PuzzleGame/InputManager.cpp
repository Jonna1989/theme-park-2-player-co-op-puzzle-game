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
	case 0: //Menu
		std::cout << "Does this even5451" << std::endl;
		if (m_keyboard->isKeyPressed(sf::Keyboard::Return))
		{
			std::cout << "Does this even" << std::endl;
			StateManager::Instance()->SetState(StateManager::InGame);
			break;
		}
		break;
	case 1: //Game
		CheckPlayerOneInput();
		break;
	}
}
void InputManager::Cleanup()
{
	delete m_keyboard;
}

void InputManager::CheckPlayerOneInput()
{
	if((m_keyboard->isKeyPressed(sf::Keyboard::A)) && (!m_keyPressedPlayer1))
	{
		m_player1->GetPlayerPiece()->MovePiece(-1);
		m_keyPressedPlayer1 = true;
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::D)) && (!m_keyPressedPlayer1))
	{
		m_player1->GetPlayerPiece()->MovePiece(1);
		m_keyPressedPlayer1 = true;
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::Q)) && (!m_keyPressedPlayer1))
	{
		m_player1->GetPlayerPiece()->RotatePiece(-1);
		m_keyPressedPlayer1 = true;
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::E)) && (!m_keyPressedPlayer1))
	{
		m_player1->GetPlayerPiece()->RotatePiece(1);
		m_keyPressedPlayer1 = true;
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::S)) && (!m_keyPressedPlayer1))
	{
		m_player1->GetPlayerPiece()->DropPieceQuickly();
		m_keyPressedPlayer1 = true;
	}

	if((!m_keyboard->isKeyPressed(sf::Keyboard::A)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::D)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::Q)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::E)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::S)))
	{
		m_keyPressedPlayer1 = false;
	}
}

void InputManager::CheckPlayerTwoInput()
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