#pragma once

#include "ScoreText.h"
#include "HighScore.h"
static const int NUMBER_OF_SCORE_POPUPS = 10;
class Score
{
public:
	Score();
	~Score();

	void Initialize				(float scorePosX, float scorePosY, int defaultScoreMultiplier, int defaultComboMultiplier, int defaultFriendBonusMultiplier);
	void Update					();
	void Cleanup				();

	int GetScore();
	void SetScore				(int newScore);
	void AddScore				(int scoreToAdd, float scoreTextPosX, float scoreTextPosY, int ownedByP1, int ownedByP2);
	int GetPreviousScore		();
	int GetScoreMultiplier		();
	void SetScoreMultiplier		(int newScoreMultiplier);
	void IncreaseScoreMultiplier(int scoreMultiplierIncrease);
	void ResetScoreMultiplier	();

	int GetComboMultiplier		();
	void SetComboMultiplier		(int newComboMultiplier);
	void IncreaseComboMultiplier(int comboMultiplierIncrease);
	void ResetComboMultiplier	();

	bool FriendBonus();

	sf::Text* GetScoreAsText	();
private:

	sf::Vector2f m_scoreTextPos;
	int m_score;
	int m_previousScore;
	int m_scoreMultiplier;
	int m_defaultScoreMultiplier;
	int m_comboMultiplier;
	int m_defaultComboMultiplier;
	int m_friendBonusMultiplier;
	sf::String m_scoreAsSfString;
	sf::String m_comboMultiplierAsSfString;
	sf::String m_previousScoreAsSfString;
	int m_scoreLastUpdate;
	int m_comboMultiplierLastUpdate;
	sf::Text* m_scoreAsText;
	sf::Text* m_comboMultiplierAsText;
	float m_comboAlpha;
	std::vector<ScoreText*> m_scoreTexts;
	int scoreTextAlternation;

	bool m_friendBonus;

	HighScore* m_highscore;
};