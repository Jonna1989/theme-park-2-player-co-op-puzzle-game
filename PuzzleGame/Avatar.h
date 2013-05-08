#pragma once
#include "TextureProvider.h"
#include "WindowManager.h"
#include "Animation.h"
#include "Load.h"

static const std::string PATH_AVATAR_FOLDER = "Assets/GraphicalAssets/TempArt/sheet";
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
	Animation* m_avatarAnimation;
};

