#include "InputManager.h"

#define m_board Board::Instance()

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
	m_gravityBase = 2000;
	m_gravity = m_gravityBase;
	m_player1Gravity = m_gravityBase;
	m_player2Gravity = m_gravityBase;
	m_keyboard = new sf::Keyboard;
	m_keyPressedPlayer1 = true;
	m_keyPressedPlayer2 = true;
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
				Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,1, DEFAULT_PITCH);
				StateManager::Instance()->SetState(StateManager::InGame);
				break;
			}
			else
			{
				CheckMusicKeys();
			}
		}
		break;
	case StateManager::InGame: //Game
		CheckPlayer1Input();
		CheckPlayer2Input();
		CheckMusicKeys();
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
	if((m_keyboard->isKeyPressed(sf::Keyboard::A)) && (!m_keyPressedPlayer1))
	{
		if (m_player1->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player1->GetPlayerPiece()->MovePiece(-1);
			m_keyPressedPlayer1 = true;
		}
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::D)) && (!m_keyPressedPlayer1))
	{
		if (m_player1->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player1->GetPlayerPiece()->MovePiece(1);
			m_keyPressedPlayer1 = true;
		}
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::Q)) && (!m_keyPressedPlayer1))
	{
		if (m_player1->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player1->GetPlayerPiece()->RotatePiece(-1);
			m_keyPressedPlayer1 = true;
		}
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::E)) && (!m_keyPressedPlayer1))
	{
		if (m_player1->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player1->GetPlayerPiece()->RotatePiece(1);
			m_keyPressedPlayer1 = true;
		}
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::S)) && (!m_keyPressedPlayer1))
	{
		if (m_player1->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player1Gravity = 100;
			Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,5,DEFAULT_PITCH);
			m_keyPressedPlayer1 = true;
		}
	}
	else if (!m_keyboard->isKeyPressed(sf::Keyboard::S) && m_player1Gravity != m_gravityBase)
	{
		m_player1Gravity = m_gravityBase;
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

void InputManager::CheckPlayer2Input()
{
	if((m_keyboard->isKeyPressed(sf::Keyboard::J)) && (!m_keyPressedPlayer2))
	{
		if (m_player2->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player2->GetPlayerPiece()->MovePiece(-1);
			m_keyPressedPlayer2 = true;
		}
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::L)) && (!m_keyPressedPlayer2))
	{
		if (m_player2->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player2->GetPlayerPiece()->MovePiece(1);
			m_keyPressedPlayer2 = true;
		}
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::U)) && (!m_keyPressedPlayer2))
	{
		if (m_player2->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player2->GetPlayerPiece()->RotatePiece(-1);
			m_keyPressedPlayer2 = true;
		}
	}
	else if((m_keyboard->isKeyPressed(sf::Keyboard::O)) && (!m_keyPressedPlayer2))
	{
		if (m_player2->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player2->GetPlayerPiece()->RotatePiece(1);
			m_keyPressedPlayer2 = true;
		}
	}

	if((m_keyboard->isKeyPressed(sf::Keyboard::K)) && (!m_keyPressedPlayer2))
	{
		if (m_player2->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player2Gravity = 100;
			Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,5,DEFAULT_PITCH);
			m_keyPressedPlayer2 = true;
		}
	}
	else if (!m_keyboard->isKeyPressed(sf::Keyboard::K) && m_player2Gravity != m_gravityBase)
	{
		m_player2Gravity = m_gravityBase;
	}

	if((!m_keyboard->isKeyPressed(sf::Keyboard::J)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::L)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::U)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::O)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::K)))
	{
		m_keyPressedPlayer2 = false;
	}
}

void InputManager::SetGravity(int gravity)
{
	m_gravity = gravity;
	m_gravityBase = gravity*5;
}

int InputManager::GetGravity()
{
	return m_gravity;
}

int InputManager::GetPlayer1Gravity()
{
	return m_player1Gravity;
}

int InputManager::GetPlayer2Gravity()
{
	return m_player2Gravity;
}

void InputManager::CheckMusicKeys()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		Music::Instance()->IncreasePitch();
		std::cout << Music::Instance()->GetPitchVariable() << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		Music::Instance()->DecreasePitch();
		std::cout << Music::Instance()->GetPitchVariable() << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		Music::Instance()->ResetPitchVariable();
		Music::Instance()->GetMusic()->setPitch(Music::Instance()->GetPitchVariable());
	}
}