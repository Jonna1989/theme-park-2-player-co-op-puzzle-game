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
	CreateSprite(m_backgroundSprite,"Assets/GraphicalAssets/TempArt/gameover.png");
	Music::Instance()->Initialize(Music::GameOverMusic1);
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
	Clean(m_backgroundSprite);
	Music::Instance()->Cleanup();
	m_highscore->Cleanup();
}
#pragma endregion