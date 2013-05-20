#include "HighScore.h"


HighScore::HighScore()
{
}
HighScore::~HighScore()
{
}
void HighScore::InitializeForIngame()
{
	LoadHighscoresToVectors();
	DeclareSfText(m_highscoresAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40, TextManager::Instance()->GetColor());
	DeclareSfText(m_highscoreNamesAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40,TextManager::Instance()->GetColor());
	ConvertIntToSfStringToSfText(m_highscore[0],m_HighscoreAsSfString,m_highscoresAsText[0],m_wordHighscore,false);
	m_highscoreNamesAsText[0]->setString("Team Name: "+m_highscoreName[0]);
	m_highscoreNamesAsText[0]->setPosition(0,40);
}
void HighScore::InitializeForGameOver()
{
	LoadHighscoresToVectors();
	DeclareSfText(m_highscoresAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40, TextManager::Instance()->GetColor());
	DeclareSfText(m_highscoreNamesAsText,TextManager::Instance()->GetFont(),NUMBER_OF_HIGHSCORES, 40, TextManager::Instance()->GetColor());
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
// 		std::string tempString;
// 		tempString.append(ConvertIntToStdString(m_highscore[i]));
// 		std::vector<char> tempChars;
// 		for(unsigned int j = 0; j < tempString.size(); j++)
// 		{
// 			tempChars.push_back(tempString[j]);
// 		}
// 		for (unsigned int j = 0; j < GetNumberOfDigits(m_highscore[i]);j++)
// 		{
// 			m_highscoreSprites[i].push_back(new sf::Sprite());
// 			SetSprite(m_highscoreSprites[i][j],"Assets/GraphicalAssets/Numbers/"+ConvertCharToStdString(tempChars[j])+".png",HIGHSCORE_POS_X,HIGHSCORE_POS_Y);
// 			Window->draw(*m_highscoreSprites[i][j]);
// 		}
		Window->draw(*m_highscoresAsText[i]);
		Window->draw(*m_highscoreNamesAsText[i]);
	}
	//LoadHighscoresToVectors();
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

void HighScore::SetHighscore(int highscore, std::string teamName)
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
void HighScore::LoadHighscoresToVectors()
{
	m_highscoreName.clear();
	m_highscore.clear();
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