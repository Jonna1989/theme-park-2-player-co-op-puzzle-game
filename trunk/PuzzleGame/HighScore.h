#pragma once
#include <fstream>
#include <iostream>
#include "Load.h"
#include "WindowManager.h"
#include "ConfigReader.h"
#include "TextManager.h"
static const std::string HIGHSCORE_FILENAME = "Assets/Highscore/Highscore.txt";
static const int NUMBER_OF_HIGHSCORES = 5;

static const float HIGHSCORE_POS_X = 10.0f;
static const float HIGHSCORE_POS_Y = 10.0f;

class HighScore
{
public:
	HighScore();
	~HighScore();

	void InitializeForIngame();
	void InitializeForGameOver();
	void UpdateInGame();
	void UpdateGameOver();
	void Cleanup();

	int GetHighscore(int highscorePosition);
	bool SetHighscore(int highscore, std::string teamName);

	void WriteHighscoreToFile(int highscore, std::string teamName);

	void LoadHighscoresToVectors();
private:



	std::vector<int> m_highscore;
	sf::String m_HighscoreAsSfString;
	std::vector<sf::Text*> m_highscoresAsText;

	std::vector<std::vector<sf::Sprite*>> m_highscoreSprites;

	ConfigReader m_configReader;

	sf::String m_wordHighscore;

	std::vector<std::string> m_highscoreName;
	sf::String m_HighscoreNameAsSfString;
	std::vector<sf::Text*> m_highscoreNamesAsText;
};

