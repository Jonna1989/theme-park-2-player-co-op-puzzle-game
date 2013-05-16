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
	DeclareSfText(m_textToDraw,charSize,textColor);
	m_isBusy = false;
	m_alpha = 255;
	m_defaultTextSize = (float)charSize;
	m_offsetY = -50.0f;
	m_scoreTextPosX = 0;
	m_scoreTextPosY = 0;
	m_scaleFactorX = 1.0f;
	m_scaleFactorY = 1.0f;

}
void ScoreText::Reset(sf::String scoreAsString, float positionX, float positionY)
{
	int textOffset = 0;
	m_stringAsCharVector.clear();
	for (unsigned int i = 0; i < scoreAsString.getSize(); i++)
	{
		m_numberSprites.push_back(new sf::Sprite());
		m_stringAsCharVector.push_back(scoreAsString[i]);
		CreateSprite(m_numberSprites[i],"Assets/Numbers/"+ConvertCharToStdString(m_stringAsCharVector[i])+".png");
		textOffset+= m_numberSprites[i]->getGlobalBounds().width;
	}
	textOffset = textOffset/2;
	for (unsigned int j = 0; j < scoreAsString.getSize(); j++)
	{
		m_numberSprites[j]->setPosition(positionX-textOffset,positionY);
		if (j > 0)
		{
			m_numberSprites[j]->setPosition(m_numberSprites[j-1]->getPosition().x+m_numberSprites[j]->getGlobalBounds().width,positionY);
		}
	}
	m_textToDraw->setString(scoreAsString);
	m_textToDraw->setPosition(positionX,positionY);
	m_alpha = 255;
	m_textSize = m_defaultTextSize;
	m_isBusy = true;
	m_offsetY = -50.0f;
	m_scaleFactorY = 1.0f;
	m_scaleFactorX = 1.0f;
}
void ScoreText::Update()
{
	if (m_isBusy == true)
	{
		if (m_alpha <= 5)
		{
			m_isBusy = false;
			for (unsigned int i = 0; i < m_numberSprites.size(); i++)
			{
				delete m_numberSprites[i];
			}
			m_numberSprites.clear();
		}
		else
		{
			
			m_textSize += (5*DeltaTime);
			m_scaleFactorX += (0.1f*DeltaTime);
			m_scaleFactorY += (0.1f*DeltaTime);
			m_textToDraw->setColor(sf::Color(0,0,0,(sf::Uint8)m_alpha));
			m_textToDraw->setCharacterSize((unsigned int)m_textSize);
			m_textToDraw->move(0, m_offsetY*DeltaTime);
			for (unsigned int i = 0; i < m_numberSprites.size(); i++)
			{
				//m_numberSprites[i]->setScale(m_scaleFactorX,m_scaleFactorY);
				m_numberSprites[i]->move(0, m_offsetY*DeltaTime);
				m_numberSprites[i]->setColor(sf::Color(255,255,255,(sf::Uint8)m_alpha));
				Window->draw(*m_numberSprites[i]);
			}
			m_alpha -= (100*DeltaTime);
			//Window->draw(*m_textToDraw);
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