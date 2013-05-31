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
	//m_highscore = new HighScore();
	//m_highscore->InitializeForStartMenu();
}

void StartMenu::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	//m_highscore->UpdateStartMenu();
	Window->display();
}

void StartMenu::Cleanup()
{
	Clean(m_backgroundSprite);
	//m_highscore->Cleanup();
	//delete m_highscore;
}

#pragma endregion