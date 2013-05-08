#pragma once
#include <fstream>
#include <iostream>
#include "Load.h"
#include "WindowManager.h"
#include "ConfigReader.h"

static const std::string HIGHSCORE_FILENAME = "Assets/Highscore/Highscore.txt";
static const int NUMBER_OF_HIGHSCORES = 5;
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
	void SetHighscore(int highscore);
private:

	void LoadHighscoresToVector();

	std::vector<int> m_highscore;
	sf::String m_HighscoreAsSfString;
	std::vector<sf::Text*> m_highscoresAsText;

	ConfigReader m_configReader;

	sf::String m_wordHighscore;

	std::vector<std::string> m_highscoreName;
	sf::String m_HighscoreNameAsSfString;
	std::vector<sf::Text*> m_highscoreNamesAsText;
};

