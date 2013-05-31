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
	m_highscore = new HighScore();
	m_highscore->InitializeForGameOver();
	m_buttonPressed = false;
	TextManager::Instance()->ResetLetters();
	DeclareSfText(m_beatHighscoreTexts,TextManager::Instance()->GetFont(),2,60,TextManager::Instance()->GetColor());
	m_beatHighscoreTexts[0]->setString("You beat one of the highscores!");
	m_beatHighscoreTexts[0]->setPosition(425,610);
	m_beatHighscoreTexts[1]->setCharacterSize(20);
	m_beatHighscoreTexts[1]->setString("Enter your teamname above,\npress the left button when you are done.");
	m_beatHighscoreTexts[1]->setPosition(715,800);
}

void GameOver::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
		if ((m_highscore->SetHighscore(TextManager::Instance()->GetScore(),TextManager::Instance()->GetTeamName()) == true) && (m_buttonPressed == false))
		{
			TextManager::Instance()->Update();
			Window->draw(*m_beatHighscoreTexts[0]);
			Window->draw(*m_beatHighscoreTexts[1]);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)||sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::U) || sf::Keyboard::isKeyPressed(sf::Keyboard::O))
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
	m_highscore->Cleanup();
}
#pragma endregion