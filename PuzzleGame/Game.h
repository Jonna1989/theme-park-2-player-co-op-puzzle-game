#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "InputManager.h"
#include "Player.h"

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
	Board* m_board;
	Player* m_player1;
	Player* m_player2;

	sf::Clock*	m_gravityClock;
	sf::Time*   m_gravityTime;
	int			m_gravityInterval;

	void Gravity();
	void UseTimedFunctions();

	void KeyCommands();
	void KeyCommand_PrintBoardToConsole();
	void KeyCommand_DropNewPiece();
	void KeyCommand_ClearBottomRow();
};

#endif