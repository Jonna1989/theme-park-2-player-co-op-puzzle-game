#ifndef BASE_H
#define BASE_H

#include "Game.h"
#include "FrameTime.h"
#include "WindowManager.h"

#include <SFML/Graphics.hpp>

class Base
{
public:
	Base();
	~Base();

	void Initialize();
	void Update();
	void Cleanup();

private:
	Game* m_game;
};

#endif