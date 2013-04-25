#pragma once
#include "TextureProvider.h"
#include "WindowManager.h"

static const std::string PATH_AVATAR_FOLDER = "Assets/GraphicalAssets/Avatars/Avatar";
static const std::string PATH_ENDING = ".png";

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Initialize(const std::string avatarName, float avatarPositionX, float avatarPositionY);//
	void Update();
	void Cleanup();

private:
	sf::Texture* m_avatarTexture;
	sf::Sprite* m_avatarSprite;
};

