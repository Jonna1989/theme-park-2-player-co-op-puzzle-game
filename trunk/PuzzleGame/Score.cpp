#include "Score.h"
#pragma region base
Score::Score()
{
	m_scoreTextPos.x = NULL;
	m_scoreTextPos.y = NULL;
	m_score = 0;
	m_previousScore = NULL;
	m_scoreMultiplier = NULL;
	m_defaultScoreMultiplier = NULL;
	m_comboMultiplier = NULL;
	m_defaultComboMultiplier = NULL;
	m_friendBonusMultiplier = NULL;
	m_scoreAsSfString = "";
	m_comboMultiplierAsSfString = "";
	m_previousScoreAsSfString = "";
	m_scoreLastUpdate = NULL;
	m_comboMultiplierLastUpdate = NULL;
	m_scoreAsText = nullptr;
	m_comboMultiplierAsText = nullptr;
	m_comboAlpha = NULL;
	m_comboAlphaLastUpdate = NULL;
	scoreTextAlternation = NULL;

	m_friendBonus = false;

	m_highscore = nullptr;
}
Score::~Score()
{
}
#pragma endregion
#pragma region Publics
void Score::Initialize(float scorePosX, float scorePosY, int defaultScoreMultiplier, int defaultComboMultiplier, int defaultFriendBonusMultiplier)
{
	m_comboAlpha = 0;
	m_scoreTextPos.x = scorePosX;
	m_scoreTextPos.y = scorePosY;
	m_defaultScoreMultiplier = defaultScoreMultiplier;
	m_defaultComboMultiplier = defaultComboMultiplier;
	m_score = 0;
	m_scoreMultiplier = m_defaultScoreMultiplier;
	m_comboMultiplier = m_defaultComboMultiplier;
	m_friendBonusMultiplier = defaultFriendBonusMultiplier;
	DeclareSfText(m_scoreAsText,TextManager::Instance()->GetFont(),50,TextManager::Instance()->GetColor(),m_scoreTextPos.x,m_scoreTextPos.y);
	DeclareSfText(m_comboMultiplierAsText,TextManager::Instance()->GetFont(),40,TextManager::Instance()->GetColor(),scorePosX+500,scorePosY+10);
	m_friendBonus = true;
	for (int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		m_scoreTexts.push_back(new ScoreText());
		m_scoreTexts[i]->Initialize(20,sf::Color::Black);
	}
	m_highscore = new HighScore();
	m_highscore->InitializeForIngame();
}
void Score::Update()
{
	m_comboAlphaLastUpdate = m_comboAlpha;
 	if ((m_score != m_scoreLastUpdate) || m_score == 0)
 	{
		ConvertIntToSfStringToSfText(m_score,m_scoreAsSfString,m_scoreAsText, "Score: ",false);
 	}
	m_scoreLastUpdate = m_score;
	if (m_comboMultiplier != m_comboMultiplierLastUpdate)
	{
		if (m_comboMultiplier != 1)
		{
			m_comboAlpha = 255;
			m_comboMultiplierAsText->setColor(sf::Color(m_comboMultiplierAsText->getColor().r,m_comboMultiplierAsText->getColor().g,m_comboMultiplierAsText->getColor().b,(sf::Uint8)m_comboAlpha));
		}
		ConvertIntToSfStringToSfText(m_comboMultiplier,m_comboMultiplierAsSfString,m_comboMultiplierAsText, "x Combo",true);
	}
	else
	{
		
		m_comboAlpha -= 50*DeltaTime;
		m_comboMultiplierAsText->setColor(sf::Color(m_comboMultiplierAsText->getColor().r,m_comboMultiplierAsText->getColor().g,m_comboMultiplierAsText->getColor().b,(sf::Uint8)m_comboAlpha));
		if (m_comboAlpha <= 0 && m_comboAlphaLastUpdate > 0)
		{
			Soundeffects::Instance()->PlaySound(0,3,1,100);
		}
	}
	m_comboMultiplierLastUpdate = m_comboMultiplier;
	for (int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		if (m_scoreTexts[i]->GetBusy() == true)
		{
			m_scoreTexts[i]->Update();
		}
	}
	Window->draw(*m_scoreAsText);
	if (m_comboMultiplier != 1)
	{
		Window->draw(*m_comboMultiplierAsText);
	}
	m_highscore->UpdateInGame();
}
void Score::Cleanup()
{
	m_highscore->SetHighscore(m_score,TextManager::Instance()->GetTeamName());
	m_highscore->Cleanup();
	for( int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		m_scoreTexts[i]->Cleanup();
	}
	m_scoreTexts.clear();
	delete m_highscore;
	delete m_scoreAsText;
	delete m_comboMultiplierAsText;

}
#pragma region Score
int Score::GetScore()
{
	return m_score;
}
void Score::SetScore(int newScore)
{
	m_score = newScore;
}
void Score::AddScore(int scoreToAdd, float scoreTextPosX, float scoreTextPosY, int ownedByP1, int ownedByP2)
{
	int P1andP2 = 0;
	m_friendBonus = true;
	P1andP2 += ownedByP1; P1andP2 += ownedByP2;
	if ((ownedByP1 == ownedByP2) && (ownedByP1 != 0) && (ownedByP2 !=0))
	{
		P1andP2*=2;
		m_friendBonus = true;
	}
	if   (((ownedByP1 == 0) || (ownedByP2 == 0)) 
		||((ownedByP1 == 0) && (ownedByP2 != 0))
		||((ownedByP2 == 0) && (ownedByP1 != 0)))
	{
		P1andP2 = 0;
		m_friendBonus = false;
	}
	m_previousScore = ((scoreToAdd*m_scoreMultiplier) + P1andP2*m_friendBonusMultiplier) * m_comboMultiplier;
	ConvertIntToSfString(m_previousScore,m_previousScoreAsSfString);
	for (int i = 0; i < NUMBER_OF_SCORE_POPUPS; i++)
	{
		if (m_scoreTexts[i]->GetBusy() == false)
		{
// 			if (m_friendBonus == true)
// 			{
// 				m_scoreTexts[i]->Reset("Buddy bonus: "+m_previousScoreAsSfString,scoreTextPosX,scoreTextPosY);
// 				break;
// 			}
// 			else
// 			{
				m_scoreTexts[i]->Reset(m_previousScoreAsSfString,scoreTextPosX,scoreTextPosY);
				break;
//			}
		}
	}
	m_score += m_previousScore;
}
#pragma endregion
int Score::GetPreviousScore()
{
	return m_previousScore;
}
#pragma region ScoreMultiplier
int Score::GetScoreMultiplier()
{
	return m_scoreMultiplier;
}
void Score::SetScoreMultiplier(int newScoreMultiplier)
{
	m_scoreMultiplier = newScoreMultiplier;
}
void Score::IncreaseScoreMultiplier(int scoreMultiplierIncrease)
{
	m_scoreMultiplier += scoreMultiplierIncrease;
}
void Score::ResetScoreMultiplier()
{
	m_scoreMultiplier = m_defaultScoreMultiplier;
}
#pragma endregion
#pragma region ComboMultiplier
int Score::GetComboMultiplier()
{
	return m_comboMultiplier;
}
void Score::SetComboMultiplier(int newComboMultiplier)
{
	m_comboMultiplier = newComboMultiplier;
}
void Score::IncreaseComboMultiplier(int comboMultiplierIncrease)
{
	m_comboMultiplier += comboMultiplierIncrease;
}
void Score::ResetComboMultiplier()
{
	m_comboMultiplier = m_defaultComboMultiplier;
}
#pragma endregion
bool Score::FriendBonus()
{
	return m_friendBonus;
}
sf::Text* Score::GetScoreAsText()
{
	return m_scoreAsText;
}
#pragma endregion

#pragma region Privates

#pragma endregion