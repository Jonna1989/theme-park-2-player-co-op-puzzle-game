#pragma once
#include "TextureProvider.h"
#include "WindowManager.h"
#include "Animation.h"
#include "Load.h"
#include "Board.h"

static const std::string PATH_AVATAR_FOLDER = "Assets/GraphicalAssets/Avatars/";
static const std::string PATH_ENDING = ".png";

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Initialize(const std::string &avatarName, float avatarPositionX, float avatarPositionY, sf::Vector2f cellSize, sf::Vector2i startPlace, int cellCount, int cellPerRow, float fps, int animationDelay, int player);
	void Update();
	void Cleanup();

	void StartHappy();
	void StartSad();

private:
	Animation* m_avatarAnimation;
	sf::Sprite* m_sprite;

	int m_player;

	sf::Clock* m_clock;
	sf::Clock* m_expressionClock;
	bool m_expressionActive;
	int m_animationCount;
	int m_animationDelay;
};

