#include "Base.h"

#pragma region Base

Base::Base()
{
	m_runtime = nullptr;
	m_timePassed = NULL;
}

Base::~Base()
{
}

void Base::Initialize()
{
	m_runtime = new sf::Clock();
	m_timePassed = 0;
	m_runtime->restart();
	TextManager::Instance()->Initialize(5,27,750,680);
	FrameTime::Instance()->Initialize();
	WindowManager::Instance()->Initialize();
	StateManager::Instance()->Initialize();
	InputManager::Instance()->Initialize();
	Soundeffects::Instance()->Initialize();
	Music::Instance()->Initialize(Music::LevelMusic1);
	srand( (int)time(0) );
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
				Window->close();
			}
		}
		if (m_runtime->getElapsedTime().asSeconds() >= 60)
		{
			m_timePassed +=60;
			m_runtime->restart();
			if (m_timePassed == 60)
			{
				std::cout << m_timePassed/60 << " minute passed since start of program!" << std::endl;
			}
			else
			{
				std::cout << m_timePassed/60 << " minutes passed since start of program!" << std::endl;
			}
		}
		StateManager::Instance()->Update();
		InputManager::Instance()->Update(StateManager::Instance()->GetState());
		FrameTime::Instance()->Update();
	}
}

void Base::Cleanup()
{
	InputManager	::Instance()->Cleanup();
	StateManager	::Instance()->Cleanup();
	WindowManager	::Instance()->Cleanup();
	FrameTime		::Instance()->Cleanup();
	TextureProvider	::Instance()->Cleanup();
	TextManager		::Instance()->Cleanup();
	Music			::Instance()->Cleanup();
	delete m_runtime;
}

#pragma endregion