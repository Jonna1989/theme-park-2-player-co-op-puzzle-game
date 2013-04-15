#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "Board.h"
#include "StateManager.h"
#include "Player.h"

class InputManager
{

public:
	InputManager();
	~InputManager();

	void Initialize();
	void Initialize(Player* player1);
	void Initialize(Player* player1, Player* player2);
	void Update(bool singlePlayer, int state);
	void Cleanup();
	
	sf::Keyboard* GetKeyboard();

	void SetPlayers(Player* player1);
	void SetPlayers(Player* player1, Player* player2);

	void CheckPlayerOneInput();
	void CheckPlayerTwoInput();

private:
	sf::Keyboard* m_keyboard;
	Board* m_board;
	Player* m_player1;
	Player* m_player2;
	bool m_keyPressedPlayer1;
	bool m_keyPressedPlayer2;
};

#endif