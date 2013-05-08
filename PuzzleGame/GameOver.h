#pragma once

#include "State.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "Music.h"
#include "HighScore.h"
class StateManager;

class GameOver:public State
{
public:
	GameOver();
	~GameOver();

	void Initialize();
	void Update();
	void Cleanup();

private:
	HighScore* m_highscore;
	sf::Texture* m_backgroundTexture;
	sf::Sprite* m_backgroundSprite;
};