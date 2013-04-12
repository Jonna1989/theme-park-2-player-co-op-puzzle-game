
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
	m_keyPressed = true;
}

void InputManager::Update(bool singlePlayer, int state)
{
	switch(state)
	{
	case StateManager::MainMenu: //Game
		CheckPlayerOneInput();
		break;
	case StateManager::InGame: //
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
<<<<<<< .mine
	if((m_keyboard->isKeyPressed(sf::Keyboard::A)) && !m_keyPressed) 
=======
	if(m_keyboard->isKeyPressed(sf::Keyboard::A)) 
>>>>>>> .r33
	{
		m_board->GetPlayerPiece()->MovePiece(-1);
		m_keyPressed = true;
	}
<<<<<<< .mine
	else if((m_keyboard->isKeyPressed(sf::Keyboard::D)) && !m_keyPressed)
=======
	else if(m_keyboard->isKeyPressed(sf::Keyboard::D))
>>>>>>> .r33
	{
		m_board->GetPlayerPiece()->MovePiece(1);
		m_keyPressed = true;
	}

<<<<<<< .mine
	if((m_keyboard->isKeyPressed(sf::Keyboard::Q)) && !m_keyPressed)
=======
	if(m_keyboard->isKeyPressed(sf::Keyboard::Q))
>>>>>>> .r33
	{
		m_board->GetPlayerPiece()->RotatePiece(-1);
		m_keyPressed = true;
	}
<<<<<<< .mine
	else if((m_keyboard->isKeyPressed(sf::Keyboard::E)) && !m_keyPressed)
=======
	else if(m_keyboard->isKeyPressed(sf::Keyboard::E))
>>>>>>> .r33
	{
		m_board->GetPlayerPiece()->RotatePiece(1);
		m_keyPressed = true;
	}

<<<<<<< .mine
	if((m_keyboard->isKeyPressed(sf::Keyboard::S)) && !m_keyPressed)
=======
	if(m_keyboard->isKeyPressed(sf::Keyboard::S))
>>>>>>> .r33
	{
		m_board->GetPlayerPiece()->DropPiece();
		m_keyPressed = true;
	}
	if ((!m_keyboard->isKeyPressed(sf::Keyboard::A)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::D)) 
		&&(!m_keyboard->isKeyPressed(sf::Keyboard::Q)) 
		&&(!m_keyboard->isKeyPressed(sf::Keyboard::E)) 
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