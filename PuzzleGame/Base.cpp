#include "Base.h"
#include "StateManager.h"
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
	}
}

void Base::Cleanup()
{
	StateManager::Instance()->Cleanup();
	WindowManager::Instance()->Cleanup();
}