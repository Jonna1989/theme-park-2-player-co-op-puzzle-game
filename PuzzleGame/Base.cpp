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
	m_window->create(sf::VideoMode(1280, 720), "Caged");

	m_loadingTexture = new sf::Texture();
	m_loadingSprite = new sf::Sprite();

	m_loadingTexture->loadFromFile("Assets/Graphics/Backgrounds/LoadingScreen.png");
	m_loadingSprite->setTexture(*m_loadingTexture);

	m_window->draw(*m_loadingSprite);
	m_window->display();

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
	delete m_loadingTexture;
	delete m_loadingSprite;

	m_game->Cleanup();
	delete m_game;

	delete m_window;
}