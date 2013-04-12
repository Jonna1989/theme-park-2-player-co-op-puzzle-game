#include "InputManager.h"
#include "StateManager.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
	m_keyboard = new sf::Keyboard;
	m_keyPressed = true;
}

void InputManager::Initialize(Board* board)
{
	m_keyboard = new sf::Keyboard;
	m_board = board;
	m_keyPressed = true;
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
	if((m_keyboard->isKeyPressed(sf::Keyboard::A)) && !m_keyPressed)
	{
		m_board->GetPlayerPiece()->MovePiece(-1);
		m_keyPressed = true;
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::D)) && !m_keyPressed)
	{
		m_board->GetPlayerPiece()->MovePiece(1);
		m_keyPressed = true;
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::Q)) && !m_keyPressed)
	{
		m_board->GetPlayerPiece()->RotatePiece(-1);
		m_keyPressed = true;
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::E)) && !m_keyPressed)
	{
		m_board->GetPlayerPiece()->RotatePiece(1);
		m_keyPressed = true;
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::S)) && !m_keyPressed)
	{
		m_board->GetPlayerPiece()->DropPiece();
		m_keyPressed = true;
	}

	if ((!m_keyboard->isKeyPressed(sf::Keyboard::A)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::D)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::Q)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::E)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::S)))
	{
		m_keyPressed = false;
	}
}

void InputManager::CheckPlayerTwoInput()
{
	if(m_keyboard->isKeyPressed(sf::Keyboard::Num4)) 
	{
		m_board->GetPlayerPiece()->MovePiece(-1);
	}
	else if(m_keyboard->isKeyPressed(sf::Keyboard::Num6))
	{
		m_board->GetPlayerPiece()->MovePiece(1);	
	}

	if(m_keyboard->isKeyPressed(sf::Keyboard::Num7))
	{
		m_board->GetPlayerPiece()->RotatePiece(-1);
	}
	else if(m_keyboard->isKeyPressed(sf::Keyboard::Num9))
	{
		m_board->GetPlayerPiece()->RotatePiece(1);
	}

	if(m_keyboard->isKeyPressed(sf::Keyboard::Num5))
	{
		m_board->GetPlayerPiece()->DropPiece();
	}
}