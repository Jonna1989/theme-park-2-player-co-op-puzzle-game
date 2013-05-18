#include "StateManager.h"

#pragma region Base

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
}

void StateManager::Initialize()
{
	State* newState = new StartMenu();
	m_listOfStates.push_back(newState);
	newState = new Game();
	m_listOfStates.push_back(newState);
	newState = new GameOver();
	m_listOfStates.push_back(newState);
	newState = new SetTeamName();
	m_listOfStates.push_back(newState);
	m_currentState = MainMenu;
	m_listOfStates[m_currentState]->Initialize();
}

void StateManager::Update()
{
	m_listOfStates[m_currentState]->Update();
}

void StateManager::Cleanup()
{
	m_listOfStates[m_currentState]->Cleanup();
	for (unsigned int i = 0; i < m_listOfStates.size(); i++)
	{
		delete m_listOfStates[i];
	}
	delete m_instance;
}

#pragma  endregion

#pragma  region Statics

StateManager* StateManager::m_instance = 0;

StateManager* StateManager::Instance()
{
	if (m_instance == 0)
	{
		m_instance = new StateManager;
	}
	return m_instance;
}

#pragma endregion


#pragma region Getters

StateManager::TypeOfState StateManager::GetState()
{
	return m_currentState;
}

std::string StateManager::GetName()
{
	std::string answer;
	switch(GetState())
	{
	case MainMenu:
		answer = "MainMenu";
		break;
	case InGame:
		answer = "InGame";
		break;
	case GameLost:
		answer = "GameLost";
		break;
	case SetName:
		answer = "SetName";
	}
	return answer;
}

#pragma endregion

#pragma region Setters

void StateManager::SetState(TypeOfState newState)
{
	std::cout << "Cleaning up: " << GetName() << std::endl;
	m_listOfStates[m_currentState]->Cleanup();
	std::cout << "Cleaned up: " << GetName() << std::endl;
	m_currentState = newState;
	std::cout << "Initializing: "<< GetName() << std::endl;
	m_listOfStates[m_currentState]->Initialize();
	std::cout << "Initialized: "<< GetName() << std::endl;
}

#pragma endregion