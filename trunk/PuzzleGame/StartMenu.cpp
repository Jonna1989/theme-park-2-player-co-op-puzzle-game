#include "StartMenu.h"

#pragma region Base

StartMenu::StartMenu()
{
}


StartMenu::~StartMenu()
{
}

#pragma endregion

#pragma region Publics

void StartMenu::Initialize()
{
	LoadTexture(m_backgroundTexture,"Assets/GraphicalAssets/TempArt/how.png");
	CreateSprite(m_backgroundSprite,m_backgroundTexture);
	Music::Instance()->Initialize(0);
	Music::Instance()->StartMusic();
}

void StartMenu::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	Window->display();
}

void StartMenu::Cleanup()
{
	Clean(m_backgroundTexture,m_backgroundSprite);
	Music::Instance()->Cleanup();
}

#pragma endregion