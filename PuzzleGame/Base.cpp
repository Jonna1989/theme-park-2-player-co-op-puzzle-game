#include "Base.h"
#include "StateManager.h"

#pragma region Base

Base::Base()
{
}

Base::~Base()
{
}

#pragma endregion

#pragma region Publics

void Base::Initialize()
{
	FrameTime::Instance()->Initialize();
	WindowManager::Instance()->Initialize();
	StateManager::Instance()->Initialize();
}

void Base::Update()
{
	while(WindowManager::Instance()->GetWindow()->isOpen())
	{
		sf::Event events;
		while(WindowManager::Instance()->GetWindow()->pollEvent(events))
		{
			if(events.type == sf::Event::Closed)
			{ WindowManager::Instance()->GetWindow()->close(); }
		}
		StateManager::Instance()->Update();
		FrameTime::Instance()->Update();
	}
}

void Base::Cleanup()
{
	StateManager::Instance()->Cleanup();
	WindowManager::Instance()->Cleanup();
}

#pragma endregion