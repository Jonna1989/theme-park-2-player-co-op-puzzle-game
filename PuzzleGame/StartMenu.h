#ifndef START_MENU_H
#define START_MENU_H

#include "State.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "Music.h"

class StateManager;
class StartMenu:public State
{
public:
	StartMenu();
	~StartMenu();

	void Initialize();
	void Update();
	void Cleanup();

private:
	sf::Texture* m_backgroundTexture;
	sf::Sprite* m_backgroundSprite;
};

#endif