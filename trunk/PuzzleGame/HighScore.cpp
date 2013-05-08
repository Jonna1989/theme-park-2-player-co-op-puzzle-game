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
	DeclareSfText(m_highscoreAsText, 40, sf::Color::Black);
	ConvertIntToSfStringToSfText(m_highscore[0],m_HighscoreAsSfString,m_highscoreAsText,m_wordHighscore,false);
	DeclareSfText(m_highscoreNameAsText, 40,sf::Color::Black);
	m_highscoreNameAsText->setString("Team Name: "+m_highscoreName[0]);
	m_highscoreNameAsText->setPosition(0,40);
}
void HighScore::InitializeForGameOver()
{
	LoadHighscoresToVector();

}
void HighScore::Update()
{
	Window->draw(*m_highscoreAsText);
	Window->draw(*m_highscoreNameAsText);
}

void HighScore::Cleanup()
{
	delete m_highscoreAsText;
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
					int temp2 = m_configReader.get("Highscore","highscore"+ConvertIntToStdString(x),temp2);
					temp.push_back(temp2);
				}
				int temp3 = 1;
				for (int y = 0; y < temp.size(); y++)
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