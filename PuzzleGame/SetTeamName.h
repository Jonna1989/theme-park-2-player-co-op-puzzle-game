#pragma once

#include "State.h"
#include "TextManager.h"
class StateManager;

class SetTeamName:public State
{
public:
	SetTeamName();
	~SetTeamName();

	void Initialize();
	void Update();
	void Cleanup();
};

