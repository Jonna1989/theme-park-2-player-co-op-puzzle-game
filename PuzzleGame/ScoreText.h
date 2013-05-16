#pragma once
#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "FrameTime.h"
#include "Load.h"
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
	std::vector<char> m_stringAsCharVector;
	std::vector<sf::Sprite*> m_numberSprites;
	float		 m_alpha;
	float		 m_defaultTextSize;
	float		 m_textSize;
	float		 m_scaleFactorX;
	float		 m_scaleFactorY;
	bool		 m_isBusy;
	float m_scoreTextPosX;
	float m_scoreTextPosY;
};

