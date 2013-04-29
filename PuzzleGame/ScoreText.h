#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "FrameTime.h"
class ScoreText
{
public:
	ScoreText();
	~ScoreText();

	void Initialize();
	void Reset(sf::Text* TextToShow, int Duration);
	void Update();
	void Cleanup();
	bool GetBusy();

private:
	sf::Clock* m_fadeClock;
	int		   m_fadeDuration;
	sf::Text*  m_textToDraw;
	sf::Uint8  m_alpha;
	bool	   m_isBusy;
};

