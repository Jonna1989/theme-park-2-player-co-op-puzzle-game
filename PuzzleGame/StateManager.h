#pragma once

#include <vector>
#include <iostream>
#include "Game.h"
class StateManager
{
public:	
	enum TypeOfState {MainMenu, InGame};
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

