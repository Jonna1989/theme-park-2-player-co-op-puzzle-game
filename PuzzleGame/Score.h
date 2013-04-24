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

	int GetScoreMultiplier();
	void SetScoreMultiplier(int newScoreMultiplier);
	void IncreaseScoreMultiplier(int scoreMultiplierIncrease);

	int GetComboMultiplier();
	void SetComboMultiplier(int newComboMultiplier);
	void IncreaseComboMultiplier(int comboMultiplierIncrease);

	sf::Text* GetScoreAsText();
private:
	sf::Vector2f m_scoreTextPos;
	int m_score;
	int m_scoreMultiplier;
	int m_comboMultiplier;
	sf::String m_scoreAsSfString;
	sf::String m_comboMultiplierAsSfString;
	void UpdateSfTextFromSfString(int intToGetStringFrom,sf::String sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo);
	int m_scoreLastUpdate;
	int m_comboMultiplierLastUpdate;
	void ConvertIntToSfString(int intToConvertFrom, sf::String &sfStringToConvertTo);
	sf::Text* m_scoreAsText;
	sf::Text* m_comboMultiplierAsText;
};

