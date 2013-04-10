
#include "InputManager.h"

InputManager::InputManager()
{
	
}

InputManager::~InputManager()
{
}

void InputManager::Initialize(Board* board)
{
	m_keyboard = new sf::Keyboard;
	m_board = board;
}

void InputManager::Update(bool singlePlayer, int state)
{
	switch(state)
	{
	case 0: //Menu?
		break;
	case 1: //Game?
		break;
	case 2: //??
		break;
	}
}
void InputManager::Cleanup()
{
	delete m_keyboard;
}

void InputManager::CheckPlayerOneInput()
{
	if(m_keyboard->isKeyPressed(sf::Keyboard::Key::A)) 
	{
		m_board->GetPlayerPiece()->MovePiece(-1);
	}
	else if(m_keyboard->isKeyPressed(sf::Keyboard::Key::D))
	{
		m_board->GetPlayerPiece()->MovePiece(1);	
	}

	if(m_keyboard->isKeyPressed(sf::Keyboard::Key::Q))
	{
		m_board->GetPlayerPiece()->RotatePiece(-1);
	}
	else if(m_keyboard->isKeyPressed(sf::Keyboard::Key::E))
	{
		m_board->GetPlayerPiece()->RotatePiece(1);
	}

	if(m_keyboard->isKeyPressed(sf::Keyboard::Key::S))
	{
		m_board->GetPlayerPiece()->DropPiece();
	}
}

void InputManager::CheckPlayerTwoInput()
{
	if(m_keyboard->isKeyPressed(sf::Keyboard::Key::Num4)) 
	{
		m_board->GetPlayerPiece()->MovePiece(-1);
	}
	else if(m_keyboard->isKeyPressed(sf::Keyboard::Key::Num6))
	{
		m_board->GetPlayerPiece()->MovePiece(1);	
	}

	if(m_keyboard->isKeyPressed(sf::Keyboard::Key::Num7))
	{
		m_board->GetPlayerPiece()->RotatePiece(-1);
	}
	else if(m_keyboard->isKeyPressed(sf::Keyboard::Key::Num9))
	{
		m_board->GetPlayerPiece()->RotatePiece(1);
	}

	if(m_keyboard->isKeyPressed(sf::Keyboard::Key::Num5))
	{
		m_board->GetPlayerPiece()->DropPiece();
	}
}