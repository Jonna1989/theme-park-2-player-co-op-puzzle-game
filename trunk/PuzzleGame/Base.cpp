#include "Base.h"

Base::Base()
{
}

Base::~Base()
{
}

void Base::Initialize()
{
	FrameTime::Instance()->Initialize();

	m_window = new sf::RenderWindow();
	m_window->create(sf::VideoMode(1920, 1080), "Puzzle Prototype");

	m_game = new Game();
	m_game->Initialize(m_window);
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
		m_game->Update();
	}
}

void Base::Cleanup()
{
	m_game->Cleanup();
	delete m_game;

	delete m_window;
}