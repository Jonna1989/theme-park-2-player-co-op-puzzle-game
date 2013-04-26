#include "ScoreText.h"

#pragma region Base
ScoreText::ScoreText()
{
}


ScoreText::~ScoreText()
{
}
#pragma endregion

void ScoreText::Initialize()
{
	m_textToDraw = new sf::Text();
	m_fadeClock = new sf::Clock();
	m_isBusy = false;
}
void ScoreText::Reset(sf::Text* TextToShow, int Duration)
{
	m_textToDraw = TextToShow;
	m_fadeDuration = Duration;
	m_fadeClock->restart();
	m_isBusy = true;
}
void ScoreText::Update()
{
	if (m_isBusy == true)
	{
		m_textToDraw->setColor(sf::Color(m_textToDraw->getColor().r,m_textToDraw->getColor().g,m_textToDraw->getColor().b,m_textToDraw->getColor().a));
		if (m_fadeClock->getElapsedTime().asMilliseconds() >= m_fadeDuration)
		{
			m_isBusy = false;
		}
		else
		{
			m_textToDraw->setPosition(m_textToDraw->getPosition().x,m_textToDraw->getPosition().y-0.3f);
			Window->draw(*m_textToDraw);
		}
	}
}
void ScoreText::Cleanup()
{
	delete m_fadeClock;
	delete m_textToDraw;
}
bool ScoreText::GetBusy()
{
	return m_isBusy;
}