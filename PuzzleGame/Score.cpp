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
void Score::Initialize(float scorePosX, float scorePosY, int defaultScoreMultiplier, int defaultComboMultiplier)
{
	m_scoreTextPos.x = scorePosX;
	m_scoreTextPos.y = scorePosY;
	m_defaultScoreMultiplier = defaultScoreMultiplier;
	m_defaultComboMultiplier = defaultComboMultiplier;
	m_score = 0;
	m_scoreMultiplier = m_defaultScoreMultiplier;
	m_comboMultiplier = m_defaultComboMultiplier;

	DeclareSfText(m_scoreAsText,50,sf::Color::Black,m_scoreTextPos);
	DeclareSfText(m_comboMultiplierAsText,40,sf::Color::Black,scorePosX+500,scorePosY+10);
	DeclareSfText(m_previousScoreAsText,20,sf::Color::Black,600,600);
	for (int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		m_scoreTexts.push_back(new ScoreText());
		m_scoreTexts[i]->Initialize();
	}
}
void Score::Update()
{
 	if (m_score != m_scoreLastUpdate)
 	{
		ConvertIntToSfStringToSfText(m_score,m_scoreAsSfString,m_scoreAsText, "Score: ",false);
 	}
	m_scoreLastUpdate = m_score;
	if (m_comboMultiplier != m_comboMultiplierLastUpdate)
	{
		ConvertIntToSfStringToSfText(m_comboMultiplier,m_comboMultiplierAsSfString,m_comboMultiplierAsText, "x Combo",true);
	}
	m_comboMultiplierLastUpdate = m_comboMultiplier;
	for (int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		if (m_scoreTexts[i]->GetBusy() == true)
		{
			m_scoreTexts[i]->Update();
		}
	}
	Window->draw(*m_scoreAsText);
	Window->draw(*m_comboMultiplierAsText);
}
void Score::Cleanup()
{
	for( int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		m_scoreTexts[i]->Cleanup();
	}
	m_scoreTexts.clear();
	delete m_scoreAsText;
	delete m_comboMultiplierAsText;
}
#pragma region Score
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
	m_previousScore = (scoreToAdd*m_scoreMultiplier)*m_comboMultiplier;
	ConvertIntToSfStringToSfText(m_previousScore,m_previousScoreAsSfString,m_previousScoreAsText);
	for (int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		if (m_scoreTexts[i]->GetBusy() == false)
		{
			m_scoreTexts[i]->Reset(m_previousScoreAsText,500);
			break;
		}
	}
	m_score += m_previousScore;
}
#pragma endregion
int Score::GetPreviousScore()
{
	return m_previousScore;
}
#pragma region ScoreMultiplier
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
void Score::ResetScoreMultiplier()
{
	m_scoreMultiplier = m_defaultScoreMultiplier;
}
#pragma endregion
#pragma region ComboMultiplier
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
void Score::ResetComboMultiplier()
{
	m_comboMultiplier = m_defaultComboMultiplier;
}
#pragma endregion
sf::Text* Score::GetScoreAsText()
{
	return m_scoreAsText;
}
void Score::SetPositionForPreviousScoreText(float x, float y)
{
	m_previousScoreAsText->setPosition(x,y);
}
#pragma endregion

#pragma region Privates
void Score::ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
void Score::ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
	if (atEnd == false)
	{
		sfStringToUpdateFrom.insert(0,addExtraText);
	}
	else
	{
		sfStringToUpdateFrom.insert(sfStringToUpdateFrom.getSize(),addExtraText);
	}
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
#pragma endregion