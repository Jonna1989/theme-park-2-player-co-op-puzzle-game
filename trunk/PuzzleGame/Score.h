#pragma once

#include <iomanip>
#include <sstream>
#include <fstream>
#include <iostream>
#include "WindowManager.h"
#include "Load.h"
#include "ScoreText.h"
static const int NUMBER_OF_SCORE_POPUPS = 5;
class Score
{
public:
	Score();
	~Score();

	//The two floats define the position of the score text that is drawn onto the screen
	//defaultScoreMultiplier is the multiplier that is multiplied with the bubbles removed to give a score
	//defaultComboMultiplier is the multiplier that multiplies the score when you have a combo going
	void Initialize(float scorePosX, float scorePosY, int defaultScoreMultiplier, int defaultComboMultiplier);
	void Update();
	void Cleanup();

	int GetScore();
	void SetScore(int newScore);
	void AddScore(int scoreToAdd);
	int GetPreviousScore		();
	int GetScoreMultiplier		();
	void SetScoreMultiplier		(int newScoreMultiplier);
	void IncreaseScoreMultiplier(int scoreMultiplierIncrease);
	void ResetScoreMultiplier	();

	int GetComboMultiplier		();
	void SetComboMultiplier		(int newComboMultiplier);
	void IncreaseComboMultiplier(int comboMultiplierIncrease);
	void ResetComboMultiplier	();

	sf::Text* GetScoreAsText();
	void SetPositionForPreviousScoreText(float x, float y);
private:

	sf::Vector2f m_scoreTextPos;
	int m_score;
	int m_previousScore;
	int m_scoreMultiplier;
	int m_defaultScoreMultiplier;
	int m_comboMultiplier;
	int m_defaultComboMultiplier;
	sf::String m_scoreAsSfString;
	sf::String m_comboMultiplierAsSfString;
	sf::String m_previousScoreAsSfString;
	int m_scoreLastUpdate;
	int m_comboMultiplierLastUpdate;
	sf::Text* m_scoreAsText;
	sf::Text* m_comboMultiplierAsText;
	sf::Text* m_previousScoreAsText;
	std::vector<ScoreText*> m_scoreTexts;
	void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo);
	void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd);
};