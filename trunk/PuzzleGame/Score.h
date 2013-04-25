#pragma once

#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include "WindowManager.h"

class Score
{
public:
	Score();
	~Score();

	void Initialize(float scorePosX, float scorePosY);
	void Update();
	void Cleanup();

	int GetScore();
	void SetScore(int newScore);
	void AddScore(int scoreToAdd);

	int GetScoreMultiplier		();
	void SetScoreMultiplier		(int newScoreMultiplier);
	void IncreaseScoreMultiplier(int scoreMultiplierIncrease);

	int GetComboMultiplier		();
	void SetComboMultiplier		(int newComboMultiplier);
	void IncreaseComboMultiplier(int comboMultiplierIncrease);

	sf::Text* GetScoreAsText();
private:
	sf::Vector2f m_scoreTextPos;
	int m_score;
	int m_scoreMultiplier;
	int m_comboMultiplier;
	sf::String m_scoreAsSfString;
	sf::String m_comboMultiplierAsSfString;
	int m_scoreLastUpdate;
	int m_comboMultiplierLastUpdate;
	sf::Text* m_scoreAsText;
	sf::Text* m_comboMultiplierAsText;
	void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition);
	void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY);
	void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo);
	void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd);
};