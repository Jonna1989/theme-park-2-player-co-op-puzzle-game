#include "GameOver.h"

#pragma region Base

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
}

#pragma endregion

#pragma region Publics

void GameOver::Initialize()
{
	m_backgroundTexture = new sf::Texture();
	m_backgroundSprite = new sf::Sprite();
	m_backgroundTexture->loadFromFile("Assets/GraphicalAssets/TempArt/menu.png");
	m_backgroundSprite->setTexture(*m_backgroundTexture);
	Music::Instance()->Initialize(0);
	Music::Instance()->StartMusic();
}

void GameOver::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	Window->display();
}

void GameOver::Cleanup()
{
	delete m_backgroundSprite;
	delete m_backgroundTexture;
	Music::Instance()->Cleanup();
}

#pragma endregion