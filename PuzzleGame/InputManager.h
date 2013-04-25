#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "Board.h"
#include "StateManager.h"
#include "Player.h"
#include "Soundeffects.h"

class InputManager
{

public:
	static InputManager* Instance();

	void Initialize();
	void Update(bool singlePlayer, int state);
	void Cleanup();
	
	sf::Keyboard* GetKeyboard();

	void SetPlayers(Player* player1);
	void SetPlayers(Player* player1, Player* player2);

	void SetGravity(int gravity);
	int GetGravity();
	int GetPlayer1Gravity();
	int GetPlayer2Gravity();

	void CheckPlayer1Input();
	void CheckPlayer2Input();

private:
	InputManager();
	~InputManager();

	static InputManager* m_instance;

	int m_gravityBase;
	int m_gravity;
	int m_player1Gravity;
	int m_player2Gravity;

	sf::Keyboard* m_keyboard;
	Player* m_player1;
	Player* m_player2;
	bool m_keyPressedPlayer1;
	sf::Event event1;
	sf::Event event2;
	bool m_keyPressedPlayer2;

	void CheckMusicKeys();
};

#endif