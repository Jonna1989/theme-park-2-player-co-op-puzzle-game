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
// 	m_game = new Game();
// 	m_game->Initialize(m_window);
}

void Base::Update()
{
	while(m_window->isOpen())
	{
		sf::Event events;
		while(m_window->pollEvent(events))
		{
			if(events.type == sf::Event::Closed)
			{ m_window->close(); }
		}
		StateManager::Instance()->Update();
	}
}

void Base::Cleanup()
{
	StateManager::Instance()->Cleanup();
	WindowManager::Instance()->Cleanup();
}