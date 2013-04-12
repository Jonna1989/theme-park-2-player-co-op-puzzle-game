#pragma once
#include "State.h"
#include "InputManager.h"
#include "WindowManager.h"
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

	InputManager* m_input;
};

