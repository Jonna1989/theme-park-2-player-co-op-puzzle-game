#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "Board.h"
class InputManager
{

public:
	InputManager();
	~InputManager();

	void Initialize();
	void Initialize(Board* board);
	void Update(bool singlePlayer, int state);
	void Cleanup();
	
	sf::Keyboard* GetKeyboard();

	void CheckPlayerOneInput();
	void CheckPlayerTwoInput();

private:
	sf::Keyboard* m_keyboard;
	Board* m_board;
	bool m_keyPressed;
};

