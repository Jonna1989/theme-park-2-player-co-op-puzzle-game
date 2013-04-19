#include "StartMenu.h"

#pragma region Base

StartMenu::StartMenu()
{
}


StartMenu::~StartMenu()
{
}

#pragma endregion

#pragma region Publics

void StartMenu::Initialize()
{
	m_backgroundTexture = new sf::Texture();
	m_backgroundSprite = new sf::Sprite();
	m_backgroundTexture->loadFromFile("Assets/GraphicalAssets/TempArt/menu.png");
	m_backgroundSprite->setTexture(*m_backgroundTexture);
	Music::Instance()->Initialize(0);
	Music::Instance()->StartMusic();
}

void StartMenu::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	Window->display();

	sf::Event events;
	while(WindowManager::Instance()->GetWindow()->pollEvent(events))
	{
		if(events.type == sf::Event::Closed)
		{
			Window->close();
		}
	}
}

void StartMenu::Cleanup()
{
	delete m_backgroundSprite;
	delete m_backgroundTexture;
	Music::Instance()->Cleanup();
}

#pragma endregion