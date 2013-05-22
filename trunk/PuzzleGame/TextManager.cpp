#include "TextManager.h"

#pragma region Base
TextManager::TextManager(void)
{
	m_position = NULL;
	m_char = NULL;
	m_numberOfLetters = NULL;
	m_numberOfCharsToEnter = NULL;
	m_charSprite = nullptr;
	m_defaultASCII = 65;
	m_transferScore = NULL;
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
	m_font = new sf::Font();
	m_font->loadFromFile("Assets/GraphicalAssets/Font/Bubblegum.ttf");
	m_color = sf::Color(168,214,81);
	for (unsigned int i = 0; i < numberOfCharsToEnter; i++)
	{
		m_textNumbers.push_back(m_defaultASCII);
		m_textNumbersAsSfText.push_back(new sf::Text());
		m_textNumbersAsSfText[i]->setFont(*m_font);
		m_textNumbersAsSfText[i]->setCharacterSize(100);
		m_textNumbersAsSfText[i]->setColor(m_color);
	}
	m_position = 0;
	m_char = 0;
	m_firstCharPos = (sf::Vector2f(firstCharPosX,firstCharPosY));
}

void TextManager::Update()
{
	for (unsigned int i = 0; i < m_textNumbersAsSfText.size(); i++)
	{
		m_textNumbersAsSfText[i]->setString(ConvertIntToChar(m_textNumbers[i]));
		if (i == 0)
		{
			m_textNumbersAsSfText[i]->setPosition(m_firstCharPos);
		}
		else
		{
			m_textNumbersAsSfText[i]->setPosition((m_textNumbersAsSfText[i-1]->getPosition().x)+(m_textNumbersAsSfText[i-1]->getGlobalBounds().width),m_textNumbersAsSfText[i-1]->getPosition().y);
		}
		if ((unsigned)m_char == i)
		{
			m_textNumbersAsSfText[i]->setColor(sf::Color(((sf::Uint8)(255)),((sf::Uint8)(255)),((sf::Uint8)(255))));
		}
		else
		{
			m_textNumbersAsSfText[i]->setColor(m_color);
		}
		Window->draw(*m_textNumbersAsSfText[i]);
	}
}
void TextManager::Cleanup()
{
	Clean(m_charSprite);
}
void TextManager::ChangeLetter(int change)
{
	m_textNumbers[m_char] += change;
	if (m_textNumbers[m_char] >= m_numberOfLetters+m_defaultASCII-1)
	{
		m_textNumbers[m_char] = m_defaultASCII;
	}
	else if (m_textNumbers[m_char] == m_defaultASCII-1)
	{
		m_textNumbers[m_char] = m_defaultASCII+m_numberOfLetters-2;
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
		tempString.append(ConvertCharToStdString(ConvertIntToChar((m_textNumbers[i]))));
	}
	return tempString;
}
sf::Font* TextManager::GetFont()
{
	return  m_font;
}
sf::Color TextManager::GetColor()
{
	return m_color;
}
int TextManager::GetScore()
{
	return m_transferScore;
}
void TextManager::SetScore(int score)
{
	m_transferScore = score;
}
void TextManager::ResetLetters()
{
	for (int i = 0; i < m_numberOfCharsToEnter ; i++)
	{
		m_textNumbers[i] = m_defaultASCII;
	}
}