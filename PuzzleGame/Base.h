#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

#include "FrameTime.h"
#include "StateManager.h"
#include "InputManager.h"
#include "Player.h"

class Base
{
public:
	Base();
	~Base();

	void Initialize();
	void Update();
	void Cleanup();

private:
};

#endif