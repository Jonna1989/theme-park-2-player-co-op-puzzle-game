#include "HighScore.h"


HighScore::HighScore()
{
}
HighScore::~HighScore()
{
}

void HighScore::Initialize()
{
	m_wordHighscore = "Highscore: ";
	if (m_configReader.load(HIGHSCORE_FILENAME))
	{
		for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++)
		{
			std::ostringstream	s;
			s << i;
			std::string i_as_string(s.str());
			int temp = 0;
			temp = m_configReader.get("Highscore","highscore"+i_as_string,temp);
			m_highscore.push_back(temp);
		}
		std::cout << "File has been read: " << HIGHSCORE_FILENAME << std::endl;
	}
	else
	{
		std::cout << "Failed to read file" << std::endl;
	}
	DeclareSfText(m_highscoreAsText, 50, sf::Color::Black);
	ConvertIntToSfStringToSfText(m_highscore[0],m_HighscoreAsSfString,m_highscoreAsText,m_wordHighscore,false);
}

void HighScore::Update()
{
	Window->draw(*m_highscoreAsText);
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
				m_configReader.add("Highscore","highscore0",highscore);
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