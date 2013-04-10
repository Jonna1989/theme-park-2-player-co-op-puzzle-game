#pragma once

#include <vector>
#include "StartMenu.h"
#include "Game.h"
#include "Highscore.h"
#include "FriendPong.h"
#include "Death.h"
#include "IntroState.h"
#include "BossStage.h"

class StateManager
{
public:	
	enum TypeOfState {MainMenu, InGame, EndMenu, Pong, DeathState, 
		Intro, Boss};
	static StateManager* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	void SetState(TypeOfState newState);
	StateManager::TypeOfState GetState();

private:
	StateManager();
	~StateManager();

	static StateManager* m_instance;

	std::vector<State*> m_listOfStates;
	TypeOfState m_currentState;
	std::string GetName();

};

