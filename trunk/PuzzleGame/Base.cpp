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
	m_input = new InputManager();
	m_input->Initialize();
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
		m_input->Update(false, StateManager::Instance()->GetState());
	}
}

void Base::Cleanup()
{
	m_input->Cleanup();
	delete m_input;
	StateManager::Instance()->Cleanup();
	WindowManager::Instance()->Cleanup();
	FrameTime::Instance()->Cleanup();
}

#pragma endregion