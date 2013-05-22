#include "HighScore.h"


HighScore::HighScore()
{
}
HighScore::~HighScore()
{
}
void HighScore::InitializeForIngame()
{
	isGameOver = false;
	LoadHighscoresToVectors();
	DeclareSfText(m_highscoresAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40, TextManager::Instance()->GetColor());
	DeclareSfText(m_highscoreNamesAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40,TextManager::Instance()->GetColor());
	ConvertIntToSfStringToSfText(m_highscore[0],m_HighscoreAsSfString,m_highscoresAsText[0],m_wordHighscore,false);
	m_highscoreNamesAsText[0]->setString("Team Name: "+m_highscoreName[0]);
	m_highscoreNamesAsText[0]->setPosition(0,40);
}
void HighScore::InitializeForGameOver()
{
	isGameOver = true;
	LoadHighscoresToVectors();
	DeclareSfText(m_highscoresAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40, TextManager::Instance()->GetColor());
	DeclareSfText(m_highscoreNamesAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40, TextManager::Instance()->GetColor());
	ReloadHighScoreTexts();
}
void HighScore::UpdateInGame()
{
	Window->draw(*m_highscoresAsText[0]);
	Window->draw(*m_highscoreNamesAsText[0]);
}
void HighScore::UpdateGameOver()
{
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		Window->draw(*m_highscoresAsText[i]);
		Window->draw(*m_highscoreNamesAsText[i]);
	}
}
void HighScore::Cleanup()
{
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		delete m_highscoresAsText[i];
		delete m_highscoreNamesAsText[i];
	}
	m_highscoresAsText.clear();
	m_highscoreNamesAsText.clear();
}

int HighScore::GetHighscore(int highscorePosition)
{
	return m_highscore[highscorePosition+1];
}

bool HighScore::SetHighscore(int highscore, std::string teamName)
{
	bool boolToReturn = false;
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		if (highscore >= m_highscore[i])
		{
			boolToReturn = true;
		}
	}
	return boolToReturn;
}
void HighScore::LoadHighscoresToVectors()
{
	m_highscoreName.clear();
	m_highscore.clear();
	m_wordHighscore = "";
	if (m_configReader.load(HIGHSCORE_FILENAME))
	{
		for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
		{
			int temp = 0;
			temp = m_configReader.get("Highscore","highscore"+ConvertIntToStdString(i),temp);
			m_highscore.push_back(temp);

			std::string tempstring;
			tempstring = m_configReader.get("HighscoreName","highscoreName"+ConvertIntToStdString(i),tempstring);
			if (isGameOver == true)
			{
				m_highscoreName.push_back(ConvertIntToStdString(i+1)+": "+(tempstring));
			}
			else
			{
				m_highscoreName.push_back(tempstring);
			}
		}
		std::cout << "File has been read: " << HIGHSCORE_FILENAME << std::endl;
	}
	else
	{
		std::cout << "Failed to read file" << std::endl;
	}
}
void HighScore::WriteHighscoreToFile(int highscore, std::string teamName)
{
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		if (highscore >= m_highscore[i])
		{
			if (m_configReader.load(HIGHSCORE_FILENAME))
			{
				std::vector<std::pair<int,std::string>>temphighscores;
				for (int x = i; x < NUMBER_OF_HIGHSCORES ; x++)
				{
					int temp2 = 0;
					temp2 = m_configReader.get("Highscore","highscore"+ConvertIntToStdString(x),temp2);
					std::string tempstring;
					tempstring = m_configReader.get("HighscoreName","highscoreName"+ConvertIntToStdString(x),tempstring);
					temphighscores.push_back(std::pair<int,std::string>(temp2,tempstring));
				}
				int temp3 = 1;
				for (unsigned int y = 0; y < temphighscores.size(); y++)
				{
					m_configReader.add("Highscore","highscore"+ConvertIntToStdString(i+temp3),temphighscores[y].first); 
					m_configReader.add("HighscoreName","highscoreName"+ConvertIntToStdString(i+temp3),temphighscores[y].second);
					temp3++;
				}
				m_configReader.add("Highscore","highscore"+ConvertIntToStdString(i),highscore);
				m_configReader.add("HighscoreName","highscoreName"+ConvertIntToStdString(i),teamName);
				m_configReader.save(HIGHSCORE_FILENAME);
				m_configReader.clear();
				break;
			}
			else
			{
				std::cout << "Failed to read: "<< HIGHSCORE_FILENAME << std::endl;
			}
		}
		else
		{
			std::cout << "You did not beat highscore "<<i<<" :(" << std::endl;
		}
	}
	LoadHighscoresToVectors();
}
void HighScore::ReloadHighScoreTexts()
{
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		ConvertIntToSfStringToSfText(m_highscore[i],m_HighscoreAsSfString,m_highscoresAsText[i],m_wordHighscore,false);
		if (i == 0)
		{
			m_highscoreNamesAsText[i]->setPosition(700.0f,300.0f);
			m_highscoresAsText[i]->setPosition(1000.0f,300.0f);
		}
		else
		{
			m_highscoreNamesAsText[i]->setPosition(m_highscoreNamesAsText[i-1]->getPosition().x,300.0f+(50*i));
			m_highscoresAsText[i]->setPosition(m_highscoresAsText[i-1]->getPosition().x,300.0f+(50*i));
		}
		m_highscoreNamesAsText[i]->setString(m_highscoreName[i]);

	}
}