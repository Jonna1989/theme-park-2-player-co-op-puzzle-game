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
	m_gravityBase = 10000;
	m_gravity = m_gravityBase;
	m_player1Gravity = m_gravityBase;
	m_player2Gravity = m_gravityBase;
	m_keyboard = new sf::Keyboard;
	m_keyPressedPlayer1 = true;
	m_keyPressedPlayer2 = true;
	m_player1 = new Player();
	m_player2 = new Player();
	for (int i = 0; i < 4; i++)
	{
		m_moveFastClocks.push_back(new sf::Clock);
		m_moveFastClocks[i]->restart();
	}
}

void InputManager::Update( int state)
{
	sf::Event event;
	switch(state)
	{
	case StateManager::MainMenu: //Menu
		while (Window->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::E || event.key.code == sf::Keyboard::U || event.key.code == sf::Keyboard::O)
			{
				Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,1, DEFAULT_PITCH,100);
				StateManager::Instance()->SetState(StateManager::InGame);
				break;
			}
			else
			{
				CheckInputsForTextmanager();
				CheckMusicKeys();
			}
			if(event.type == sf::Event::Closed)
			{
				Window->close();
			}
		}
		break;
	case StateManager::SetName:
		while (Window->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::L)
			{
				Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,1, DEFAULT_PITCH,100);
				StateManager::Instance()->SetState(StateManager::InGame);
				break;
			}
			else
			{
				CheckInputsForTextmanager();
				CheckMusicKeys();
			}
			if(event.type == sf::Event::Closed)
			{
				Window->close();
			}
		}

		break;
	case StateManager::InGame: //Game
		CheckPlayer1Input();
		CheckPlayer2Input();
		CheckMusicKeys();
		break;
	case StateManager::GameLost: //GameOver
		while (Window->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Q)
			{
				Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,1, DEFAULT_PITCH,100);
				StateManager::Instance()->SetState(StateManager::MainMenu);
				break;
			}
			else
			{
				CheckMusicKeys();
				CheckInputsForTextmanager();
			}
			if(event.type == sf::Event::Closed)
			{
				Window->close();
			}
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
	CheckInputsGame(m_player1,m_keyPressedPlayer1,sf::Keyboard::A,-1,0,false);
	CheckInputsGame(m_player1,m_keyPressedPlayer1,sf::Keyboard::D,1,0,false);
	CheckInputsGame(m_player1,m_keyPressedPlayer1,sf::Keyboard::Q,-1,0,true);
	CheckInputsGame(m_player1,m_keyPressedPlayer1,sf::Keyboard::E,1,0,true);
	if((m_keyboard->isKeyPressed(sf::Keyboard::S)) && (!m_keyPressedPlayer1))
	{
		if (m_player1->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player1Gravity = 100;
			PlayRotateSound
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
		m_moveFastClocks[0]->restart();
	}
}

void InputManager::CheckPlayer2Input()
{
	CheckInputsGame(m_player2,m_keyPressedPlayer2,sf::Keyboard::J,-1,2,false);
	CheckInputsGame(m_player2,m_keyPressedPlayer2,sf::Keyboard::L, 1,2,false);
	CheckInputsGame(m_player2,m_keyPressedPlayer2,sf::Keyboard::U,-1,2,true);
	CheckInputsGame(m_player2,m_keyPressedPlayer2,sf::Keyboard::O, 1,2,true);
	if((m_keyboard->isKeyPressed(sf::Keyboard::K)) && (!m_keyPressedPlayer2))
	{
		if (m_player2->GetPlayerPiece()->GetOwner() != 0)
		{
			m_player2Gravity = 100;
			PlayRotateSound
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
		m_moveFastClocks[2]->restart();
	}
}
void InputManager::CheckInputsForTextmanager()
{
	CheckInputsText(m_keyPressedPlayer1,sf::Keyboard::A,-1,0,false);
	CheckInputsText(m_keyPressedPlayer1,sf::Keyboard::D,1,0,false);
	CheckInputsText(m_keyPressedPlayer1,sf::Keyboard::W,-1,0,true);
	CheckInputsText(m_keyPressedPlayer1,sf::Keyboard::S,1,0,true);
	if((!m_keyboard->isKeyPressed(sf::Keyboard::A)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::D)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::W)) 
		&& (!m_keyboard->isKeyPressed(sf::Keyboard::S))) 
	{
		m_keyPressedPlayer1 = false;
		m_moveFastClocks[0]->restart();
	}
}
void InputManager::SetGravity(int gravity)
{
	m_gravity = gravity;
	m_gravityBase = gravity;
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
void InputManager::CheckInputsGame(Player* &player,bool &playerPressedKey, sf::Keyboard::Key key, int dir, int clock, bool rotate)
{
	if( ( (m_keyboard->isKeyPressed(key)) && (!playerPressedKey))
		||((m_keyboard->isKeyPressed(key)) && ( m_moveFastClocks[clock]->getElapsedTime().asMilliseconds() > 500) && (m_moveFastClocks[clock+1]->getElapsedTime().asMilliseconds() > 100)))
	{
		if (player->GetPlayerPiece()->GetOwner() != 0)
		{
			if (rotate)
			{
				player->GetPlayerPiece()->RotatePiece(dir);
				playerPressedKey = true;
			}
			else
			{
				player->GetPlayerPiece()->MovePiece(dir);
				playerPressedKey = true;
			}
		}
		m_moveFastClocks[clock+1]->restart();
	}
}
void InputManager::CheckInputsText(bool &playerPressedKey, sf::Keyboard::Key key, int dir, int clock, bool letterChange)
{
	if( ( (m_keyboard->isKeyPressed(key)) && (!playerPressedKey))
		||((m_keyboard->isKeyPressed(key)) && ( m_moveFastClocks[clock]->getElapsedTime().asMilliseconds() > 500) && (m_moveFastClocks[clock+1]->getElapsedTime().asMilliseconds() > 100)))
	{
		if (letterChange)
		{
			TextManager::Instance()->ChangeLetter(dir);
			playerPressedKey = true;
		}
		else
		{
			TextManager::Instance()->ChangeSelection(dir);
			playerPressedKey = true;
		}
		m_moveFastClocks[clock+1]->restart();
	}
}