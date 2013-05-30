#include "StartMenu.h"

#pragma region Base

StartMenu::StartMenu()
{
	m_backgroundSprite = nullptr;
}


StartMenu::~StartMenu()
{
}

#pragma endregion

#pragma region Publics

void StartMenu::Initialize()
{
	CreateSprite(m_backgroundSprite,"Assets/GraphicalAssets/TempArt/how.png");
	TextManager::Instance()->ResetLetters();
	Music::Instance()->Initialize(0);
}

void StartMenu::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
//	TextManager::Instance()->Update();
	Window->display();
}

void StartMenu::Cleanup()
{
	Clean(m_backgroundSprite);
	Music::Instance()->Cleanup();
}

#pragma endregion