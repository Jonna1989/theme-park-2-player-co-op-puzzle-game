#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include "Board.h"
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
//	InputManager* m_input;
	InputManager* m_input;
};

