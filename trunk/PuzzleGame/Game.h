#ifndef GAME_H
#define GAME_H


#include "State.h"
#include "InputManager.h"

class StateManager;

class Game:public State
{
public:
	Game();
	~Game();

	void Initialize();
	void Update();
	void Cleanup();

private:
	Board* m_board;
	InputManager* m_input;
};

#endif