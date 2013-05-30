#include "GameOver.h"

#pragma region Base

GameOver::GameOver()
{
	m_highscore = nullptr;
	m_backgroundSprite = nullptr;
	m_buttonPressed = false;
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
	m_highscore = new HighScore();
	m_highscore->InitializeForGameOver();
	m_buttonPressed = false;
	TextManager::Instance()->ResetLetters();
	DeclareSfText(m_beatHighscoreText,TextManager::Instance()->GetFont(),60,TextManager::Instance()->GetColor(),400,400);
	m_beatHighscoreText->setString("You beat one of the highscores! Enter your teamname below, press the left button when you are done.");
}

void GameOver::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);

		if ((m_highscore->SetHighscore(TextManager::Instance()->GetScore(),TextManager::Instance()->GetTeamName()) == true) && (m_buttonPressed == false))
		{
			TextManager::Instance()->Update();
			Window->draw(*m_beatHighscoreText);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				m_highscore->WriteHighscoreToFile(TextManager::Instance()->GetScore(),TextManager::Instance()->GetTeamName());
				m_buttonPressed = true;
				m_highscore->LoadHighscoresToVectors();
				m_highscore->ReloadHighScoreTexts();

			}
		}

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