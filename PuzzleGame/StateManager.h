#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <vector>
#include <iostream>
#include "Game.h"
#include "StartMenu.h"
#include "GameOver.h"

class StateManager
{
public:	
	enum TypeOfState {MainMenu, InGame, GameLost};
	static StateManager* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	StateManager::TypeOfState GetState();
	void SetState(TypeOfState newState);

private:
	StateManager();
	~StateManager();

	static StateManager* m_instance;

	std::vector<State*> m_listOfStates;
	TypeOfState m_currentState;

	std::string GetName();
};

#endif