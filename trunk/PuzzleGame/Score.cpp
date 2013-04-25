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

	DeclareSfText(m_scoreAsText,50,sf::Color::Black,m_scoreTextPos);
	DeclareSfText(m_comboMultiplierAsText,40,sf::Color::Black,scorePosX+400,scorePosY+10);
}
void Score::Update()
{
 	if (m_score != m_scoreLastUpdate)
 	{
		ConvertIntToSfStringToSfText(m_score,m_scoreAsSfString,m_scoreAsText);
 	}
	m_scoreLastUpdate = m_score;
	if (m_comboMultiplier != m_comboMultiplierLastUpdate)
	{
		ConvertIntToSfStringToSfText(m_comboMultiplier,m_comboMultiplierAsSfString,m_comboMultiplierAsText, "x Combo");
	}
	m_comboMultiplierLastUpdate = m_comboMultiplier;
	Window->draw(*m_scoreAsText);
	Window->draw(*m_comboMultiplierAsText);
}
void Score::Cleanup()
{
	delete m_scoreAsText;
	delete m_comboMultiplierAsText;
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
void Score::DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition)
{
	textToDeclare = new sf::Text();
	textToDeclare->setCharacterSize(charSize);
	textToDeclare->setColor(textColor);
	textToDeclare->setPosition(textPosition);
}
void Score::DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY)
{
	textToDeclare = new sf::Text();
	textToDeclare->setCharacterSize(charSize);
	textToDeclare->setColor(textColor);
	textToDeclare->setPosition(textPositionX,textPositionY);
}
void Score::ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
void Score::ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addAtEnd)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
	sfStringToUpdateFrom.insert(sfStringToUpdateFrom.getSize(),addAtEnd);
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
#pragma endregion