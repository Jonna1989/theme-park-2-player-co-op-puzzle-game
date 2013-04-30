#include "ScoreText.h"

#pragma region Base
ScoreText::ScoreText()
{
}


ScoreText::~ScoreText()
{
}
#pragma endregion

void ScoreText::Initialize(unsigned int charSize, const sf::Color textColor)
{
	m_textToDraw = new sf::Text();
	m_textToDraw->setCharacterSize(charSize);
	m_textToDraw->setColor(textColor);
	m_isBusy = false;
	m_alpha = 255;
	m_offsetY = -50.0f;
	m_scoreTextPosX = 0;
	m_scoreTextPosY = 0;
}
void ScoreText::Reset(sf::String scoreAsString, float positionX, float positionY)
{
	m_textToDraw->setString(scoreAsString);
	m_textToDraw->setPosition(positionX,positionY);
	m_alpha = 255;
	m_isBusy = true;
	m_offsetY = -50.0f;
}
void ScoreText::Update()
{
	if (m_isBusy == true)
	{
		if (m_alpha <= 0)
		{
			m_isBusy = false;
		}
		else
		{
			m_alpha -= (50*DeltaTime);
			m_textToDraw->setColor(sf::Color(m_textToDraw->getColor().r,
											 m_textToDraw->getColor().g,
											 m_textToDraw->getColor().b,
											 m_alpha));
			m_textToDraw->move(0, m_offsetY*DeltaTime);
			Window->draw(*m_textToDraw);
		}
	}
}
void ScoreText::Cleanup()
{
	delete m_textToDraw;
}
bool ScoreText::GetBusy()
{
	return m_isBusy;
}