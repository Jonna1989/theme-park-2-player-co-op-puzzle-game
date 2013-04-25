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
	LoadTexture(m_backgroundTexture, "Assets/GraphicalAssets/TempArt/menu.png");
	CreateSprite(m_backgroundSprite,m_backgroundTexture);
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
	Clean(m_backgroundTexture,m_backgroundSprite);
	Music::Instance()->Cleanup();
}

#pragma endregion