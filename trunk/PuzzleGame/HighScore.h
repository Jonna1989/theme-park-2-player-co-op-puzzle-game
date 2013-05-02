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

	void Initialize();
	void Update();
	void Cleanup();

	int GetHighscore(int highscorePosition);
	void SetHighscore(int highscore);
private:
	std::vector<int> m_highscore;
	sf::String m_HighscoreAsSfString;
	sf::Text* m_highscoreAsText;

	ConfigReader m_configReader;

	sf::String m_wordHighscore;

	std::vector<std::string> m_highscoreName;
	sf::String m_HighscoreNameAsSfString;
	sf::Text* m_highscoreNameAsText;
};

