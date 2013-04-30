#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "FrameTime.h"
#include "StateManager.h"
#include "InputManager.h"
#include "Player.h"
#include "Soundeffects.h"
#include "TextureProvider.h"
#include "Board.h"

class Base
{
public:
	Base();
	~Base();

	void Initialize();
	void Update();
	void Cleanup();

private:
	sf::Clock* m_runtime;
	int m_timePassed;
};

#endif