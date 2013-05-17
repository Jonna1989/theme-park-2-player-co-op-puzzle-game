#include "TextManager.h"

#pragma region Base
TextManager::TextManager(void)
{
}
TextManager::~TextManager(void)
{
}
#pragma endregion

void TextManager::Initialize(unsigned int numberOfCharsToEnter, unsigned int numberOfLetters)
{
	for (int i = 0; i < numberOfCharsToEnter; i++)
	{
		for (int k = 0; k < numberOfLetters ; k++)
		{
			m_textNumbers[i].push_back(k);
		}
	}
}

void TextManager::Update()
{

}

void TextManager::Cleanup()
{

}