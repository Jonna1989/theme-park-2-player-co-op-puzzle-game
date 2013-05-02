#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "FrameTime.h"
class ScoreText
{
public:
	ScoreText();
	~ScoreText();

	void Initialize(unsigned int charSize, const sf::Color textColor);
	void Reset(sf::String scoreAsString, float positionX, float positionY);
	void Update();
	void Cleanup();
	bool GetBusy();

private:
	float		 m_offsetY;
	sf::Text*	 m_textToDraw;
	float	 m_alpha;
	bool		 m_isBusy;
	float m_scoreTextPosX;
	float m_scoreTextPosY;
};

