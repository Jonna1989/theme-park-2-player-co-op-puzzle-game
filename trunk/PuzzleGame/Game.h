#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "InputManager.h"
#include "Player.h"
#include "ParticleEffect.h"
#include "Avatar.h"
#include "PowerItem.h"
#include "ColorBomb.h"
#include "Bomb.h"
#include "Thorn.h"
#include "ScoreText.h"

#include <stdlib.h>

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

	Avatar* m_player1Avatar;
	Avatar* m_player2Avatar;

	sf::Clock*	m_gravityClock;
	int			m_gravityInterval;

	sf::Clock*	m_increaseClock;
	int m_increaseInterval;

	sf::Clock*	m_player1Clock;
	sf::Clock*	m_player2Clock;

	sf::Clock* m_printBoardInterval;

	void Gravity();
	void BoardGravity();
	void UseTimedFunctions();

	void KeyCommands();
	void KeyCommand_PrintBoardToConsole();
	void KeyCommand_ClearBottomRow();
	void KeyCommand_DropBomb();
	void KeyCommand_DropColorBomb();
	void KeyCommand_DropThorn();

	sf::Sprite* m_speedUpSprite;
	float m_speedUpSpriteAlpha;

	Bomb* b;
	ColorBomb* cb;
	Thorn* t;
	bool keyPressedThorn;
	bool keyPressedBomb;
	bool keyPressedColorBomb;
};

#endif