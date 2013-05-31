#ifndef START_MENU_H
#define START_MENU_H

#include "State.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "Music.h"
#include "TextManager.h"
#include "HighScore.h"
class StateManager;
class StartMenu:public State
{
public:
	StartMenu();
	~StartMenu();

	void Initialize();
	void Update();
	void Cleanup();
	bool GetHelp();
	void SetHelp(bool help);
private:
	sf::Sprite* m_backgroundSprite;
	HighScore* m_highscore;
	bool m_showHelp;
	sf::Keyboard m_keyboard;
};

#endif