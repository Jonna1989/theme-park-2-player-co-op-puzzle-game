#pragma once

#include "Game.h"
#include "FrameTime.h"

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
	sf::RenderWindow* m_window;

	Game* m_game;
};
