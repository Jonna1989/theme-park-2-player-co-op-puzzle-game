#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class StateManager;
class Game:public State
{
public:
	Game();
	~Game();

	void Initialize();
	void Update();
	void Cleanup();
};

