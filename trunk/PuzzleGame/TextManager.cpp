#include "TextManager.h"

#pragma region Base
TextManager::TextManager(void)
{
	m_position = NULL;
	m_char = NULL;
	m_numberOfLetters = NULL;
	m_numberOfCharsToEnter = NULL;
	m_charSprite = nullptr;
}
TextManager::~TextManager(void)
{
}
#pragma endregion

TextManager* TextManager::m_instance = 0;

TextManager* TextManager::Instance()
{
	if(m_instance == 0)
	{
		m_instance = new TextManager();
	}

	return m_instance;
}
void TextManager::Initialize(unsigned int numberOfCharsToEnter, unsigned int numberOfLetters, float firstCharPosX, float firstCharPosY)
{
	m_numberOfCharsToEnter = numberOfCharsToEnter;
	m_numberOfLetters = numberOfLetters;
	for (unsigned int i = 0; i < numberOfCharsToEnter; i++)
	{
		m_textNumbers.push_back(0);
	}
	m_position = 0;
	m_char = 0;
	m_firstCharPos = (sf::Vector2f(firstCharPosX,firstCharPosY));
}

void TextManager::Update()
{
	for (int i = 0; i < m_numberOfCharsToEnter ; i++)
	{
		if (i == 0)
		{
			CreateSprite(m_charSprite,("Assets/GraphicalAssets/Letters/"+ConvertIntToStdString(m_textNumbers[i])+".png"));
			m_charSprite->setPosition(m_firstCharPos);
		}
		else
		{
			m_charSprite->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Letters/"+ConvertIntToStdString(m_textNumbers[i])+".png"));
			m_charSprite->move(m_charSprite->getGlobalBounds().width,0);
		}
		Window->draw(*m_charSprite);
	}
	m_charSprite->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Letters/marking.png"));
	m_charSprite->setPosition(m_firstCharPos.x+(100*m_char),m_firstCharPos.y);
	Window->draw(*m_charSprite);
}
void TextManager::Cleanup()
{
	Clean(m_charSprite);
}
void TextManager::ChangeLetter(int change)
{
	m_textNumbers[m_char] += change;
	if (m_textNumbers[m_char] >= m_numberOfLetters)
	{
		m_textNumbers[m_char] = 0;
	}
	else if (m_textNumbers[m_char] == -1)
	{
		m_textNumbers[m_char] = m_numberOfLetters-1;
	}
}
void TextManager::ChangeSelection(int change)
{
	m_char += change;
	if (m_char >= m_numberOfCharsToEnter )
	{
		m_char = 0;
	}
	else if (m_char == -1)
	{
		m_char = m_numberOfCharsToEnter - 1;
	}
}
std::string TextManager::GetTeamName()
{
	std::string tempString;
	for (int i = 0; i < m_numberOfCharsToEnter; i++)
	{
		tempString.append(ConvertIntToStdString(m_textNumbers[i]));
	}
	return tempString;
}