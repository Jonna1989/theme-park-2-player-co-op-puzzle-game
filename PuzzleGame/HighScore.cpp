#include "HighScore.h"


HighScore::HighScore()
{
}
HighScore::~HighScore()
{
}
void HighScore::InitializeForIngame()
{
	LoadHighscoresToVector();
	DeclareSfText(m_highscoresAsText,NUMBER_OF_HIGHSCORES, 40, sf::Color::Black);
	ConvertIntToSfStringToSfText(m_highscore[0],m_HighscoreAsSfString,m_highscoresAsText[0],m_wordHighscore,false);
	DeclareSfText(m_highscoreNamesAsText,NUMBER_OF_HIGHSCORES, 40,sf::Color::Black);
	m_highscoreNamesAsText[0]->setString("Team Name: "+m_highscoreName[0]);
	m_highscoreNamesAsText[0]->setPosition(0,40);
}
void HighScore::InitializeForGameOver()
{
	LoadHighscoresToVector();
	DeclareSfText(m_highscoresAsText,NUMBER_OF_HIGHSCORES, 40, sf::Color::White);
	DeclareSfText(m_highscoreNamesAsText,NUMBER_OF_HIGHSCORES, 40,sf::Color::White);
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		ConvertIntToSfStringToSfText(m_highscore[i],m_HighscoreAsSfString,m_highscoresAsText[i],m_wordHighscore,false);
		m_highscoresAsText[i]->setPosition(500.0f,40.0f*(float)i);
		m_highscoreNamesAsText[i]->setString("Team Name: "+m_highscoreName[i]);
		m_highscoreNamesAsText[i]->setPosition(1000.0f,40.0f*(float)i);
	}
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

void HighScore::SetHighscore(int highscore)
{
	for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
	{
		if (highscore >= m_highscore[i])
		{
			if (m_configReader.load(HIGHSCORE_FILENAME))
			{
				std::vector<int> temp;
				for (int x = i; x < NUMBER_OF_HIGHSCORES ; x++)
				{
					int temp2 = 0;
					temp2 = m_configReader.get("Highscore","highscore"+ConvertIntToStdString(x),temp2);
					temp.push_back(temp2);
				}
				int temp3 = 1;
				for (unsigned int y = 0; y < temp.size(); y++)
				{
					m_configReader.add("Highscore","highscore"+ConvertIntToStdString(i+temp3),temp[y]); 
					temp3++;
				}
				m_configReader.add("Highscore","highscore"+ConvertIntToStdString(i),highscore);
				m_configReader.save(HIGHSCORE_FILENAME);
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
}
void HighScore::LoadHighscoresToVector()
{
	m_wordHighscore = "Highscore: ";
	if (m_configReader.load(HIGHSCORE_FILENAME))
	{
		for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
		{
			int temp = 0;
			temp = m_configReader.get("Highscore","highscore"+ConvertIntToStdString(i),temp);
			m_highscore.push_back(temp);

			std::string tempstring;
			tempstring = m_configReader.get("HighscoreName","highscoreName"+ConvertIntToStdString(i),tempstring);
			m_highscoreName.push_back(tempstring);
		}
		std::cout << "File has been read: " << HIGHSCORE_FILENAME << std::endl;
	}
	else
	{
		std::cout << "Failed to read file" << std::endl;
	}
}