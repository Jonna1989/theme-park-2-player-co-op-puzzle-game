#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "InputManager.h"
#include "Player.h"
#include "ParticleEffect.h"

class StateManager;

class Game:public State
{
public:
	Game();
	~Game();

	void Initialize();
	void Update();
	void Cleanup();

	int GetGravityInterval();
	
	void SetGravityInterval(int milliSeconds);

private:
	Player* m_player1;
	Player* m_player2;

	sf::Clock*	m_gravityClock;
	int			m_gravityInterval;

	sf::Clock*	m_player1Clock;
	sf::Clock*	m_player2Clock;

	void Gravity();
	void BoardGravity();
	void UseTimedFunctions();

	void KeyCommands();
	void KeyCommand_PrintBoardToConsole();
	void KeyCommand_ClearBottomRow();
};

#endif