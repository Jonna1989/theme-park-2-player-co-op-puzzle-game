#pragma once
#include "Load.h"
#include "WindowManager.h"
#include "TextureProvider.h"
class TextManager
{
public:
	static TextManager* Instance();


	void Initialize(unsigned int numberOfCharsToEnter, unsigned int numberOfLetters, float firstCharPosX, float firstCharPosY);
	void Update();
	void Cleanup();

	void ChangeLetter(int change);
	void ChangeSelection(int change);
	std::string GetTeamName();
private:
	TextManager();
	~TextManager();

	static TextManager* m_instance;

	std::vector<int> m_textNumbers;
	int m_position;
	int m_char;
	int m_numberOfLetters;
	int m_numberOfCharsToEnter;
	int m_teamName;
	sf::Vector2f m_firstCharPos;
	
	sf::Sprite* m_charSprite;
};
