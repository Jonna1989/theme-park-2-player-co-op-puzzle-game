#include "Score.h"

#pragma region base
Score::Score()
{
}


Score::~Score()
{
}
#pragma endregion
#pragma region Publics
void Score::Initialize(float scorePosX, float scorePosY)
{
	m_scoreTextPos.x = scorePosX;
	m_scoreTextPos.y = scorePosY;
	m_score = 0;
	m_comboMultiplier = 1;
	m_scoreMultiplier = 10;

	m_scoreAsText = new sf::Text();
	m_scoreAsText->setCharacterSize(50);
	m_scoreAsText->setColor(sf::Color::Black);
	m_scoreAsText->setPosition(m_scoreTextPos);
	UpdateSfTextFromSfString(m_score,m_scoreAsSfString,m_scoreAsText);

	m_comboMultiplierAsText = new sf::Text();
	m_comboMultiplierAsText->setCharacterSize(50);
	m_comboMultiplierAsText->setColor(sf::Color::Black);
	m_comboMultiplierAsText->setPosition(scorePosX+400,scorePosY);
	UpdateSfTextFromSfString(m_comboMultiplier,m_comboMultiplierAsSfString,m_comboMultiplierAsText);
}
void Score::Update()
{
 	if (m_score != m_scoreLastUpdate)
 	{
		UpdateSfTextFromSfString(m_score,m_scoreAsSfString,m_scoreAsText);
 	}
	m_scoreLastUpdate = m_score;
	if (m_comboMultiplier != m_comboMultiplierLastUpdate)
	{
		UpdateSfTextFromSfString(m_comboMultiplier,m_comboMultiplierAsSfString,m_comboMultiplierAsText);
	}
	m_comboMultiplierLastUpdate = m_comboMultiplier;
	Window->draw(*m_scoreAsText);
	Window->draw(*m_comboMultiplierAsText);
}
void Score::Cleanup()
{

}

int Score::GetScore()
{
	return m_score;
}
void Score::SetScore(int newScore)
{
	m_score = newScore;
}
void Score::AddScore(int scoreToAdd)
{
	m_score += (scoreToAdd*m_scoreMultiplier)*m_comboMultiplier;
}

int Score::GetScoreMultiplier()
{
	return m_scoreMultiplier;
}
void Score::SetScoreMultiplier(int newScoreMultiplier)
{
	m_scoreMultiplier = newScoreMultiplier;
}
void Score::IncreaseScoreMultiplier(int scoreMultiplierIncrease)
{
	m_scoreMultiplier += scoreMultiplierIncrease;
}

int Score::GetComboMultiplier()
{
	return m_comboMultiplier;
}
void Score::SetComboMultiplier(int newComboMultiplier)
{
	m_comboMultiplier = newComboMultiplier;
}
void Score::IncreaseComboMultiplier(int comboMultiplierIncrease)
{
	m_comboMultiplier += comboMultiplierIncrease;
}

sf::Text* Score::GetScoreAsText()
{
	return m_scoreAsText;
}

#pragma endregion

#pragma region Privates
void Score::UpdateSfTextFromSfString(int intToGetStringFrom,sf::String sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo)
{
	ConvertIntToSfString(intToGetStringFrom,sfStringToUpdateFrom);
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
void Score::ConvertIntToSfString(int intToConvertFrom, sf::String &sfStringToConvertTo)
{
	std::ostringstream convert;
	convert << intToConvertFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToConvertTo = tempStdString;
}
#pragma endregion