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
	CreateSprite(m_backgroundSprite,"Assets/GraphicalAssets/TempArt/how.png");
	Music::Instance()->Initialize(0);
}

void StartMenu::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	Window->display();
}

void StartMenu::Cleanup()
{
	Clean(m_backgroundSprite);
	Music::Instance()->Cleanup();
}

#pragma endregion