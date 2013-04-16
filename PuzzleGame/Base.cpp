#include "Base.h"

#pragma region Base

Base::Base()
{
}

Base::~Base()
{
}

void Base::Initialize()
{
	FrameTime::Instance()->Initialize();
	WindowManager::Instance()->Initialize();
	StateManager::Instance()->Initialize();
	InputManager::Instance()->Initialize();

	srand((int)time((0)));
}

void Base::Update()
{
	while(WindowManager::Instance()->GetWindow()->isOpen())
	{
		sf::Event events;
		while(WindowManager::Instance()->GetWindow()->pollEvent(events))
		{
			if(events.type == sf::Event::Closed)
			{
				WindowManager::Instance()->GetWindow()->close();
			}
		}
		StateManager::Instance()->Update();
		FrameTime::Instance()->Update();
		InputManager::Instance()->Update(false, StateManager::Instance()->GetState());
	}
}

void Base::Cleanup()
{
	InputManager::Instance()->Cleanup();
	StateManager::Instance()->Cleanup();
	WindowManager::Instance()->Cleanup();
	FrameTime::Instance()->Cleanup();
}

#pragma endregion