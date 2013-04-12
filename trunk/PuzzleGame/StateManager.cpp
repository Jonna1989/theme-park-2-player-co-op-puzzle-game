#include "StateManager.h"

#pragma region Base
StateManager::StateManager(void)
{
}


StateManager::~StateManager(void)
{

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

#pragma region Publics
#pragma region Initalize
void StateManager::Initialize()
{
	State* newState = new StartMenu();
	m_listOfStates.push_back(newState);
	newState = new Game();
	m_listOfStates.push_back(newState);

	m_currentState = MainMenu;
	m_listOfStates[m_currentState]->Initialize();
}
#pragma endregion
#pragma region Update
void StateManager::Update()
{
	m_listOfStates[m_currentState]->Update();
}
#pragma endregion
#pragma region Cleanup
void StateManager::Cleanup()
{
	m_listOfStates[m_currentState]->Cleanup();
	for (unsigned int i = 0; i < m_listOfStates.size(); i++)
	{
		delete m_listOfStates[i];
	}
}
#pragma endregion
#pragma region SetState
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

StateManager::TypeOfState StateManager::GetState()
{
	return m_currentState;
}

#pragma endregion
std::string StateManager::GetName()
{
	std::string answer;
	switch(GetState())
	{
		case MainMenu:
			{
				answer = "MainMenu";
				break;
			}
		case InGame:
			{
				answer = "InGame";
				break;
			}
	}
	return answer;
}
#pragma endregion