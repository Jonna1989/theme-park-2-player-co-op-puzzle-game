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
	LoadTexture(m_backgroundTexture, "Assets/GraphicalAssets/TempArt/gameover.png");
	CreateSprite(m_backgroundSprite,m_backgroundTexture);
	Music::Instance()->Initialize(Music::MenuMusic1);
	Music::Instance()->StartMusic();
	m_highscore = new HighScore();
	m_highscore->InitializeForGameOver();
}

void GameOver::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	m_highscore->UpdateGameOver();
	Window->display();
}

void GameOver::Cleanup()
{
	Clean(m_backgroundTexture,m_backgroundSprite);
	Music::Instance()->Cleanup();
	m_highscore->Cleanup();
}

#pragma endregion