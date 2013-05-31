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
	m_highscore = new HighScore();
	m_highscore->InitializeForStartMenu();
	m_showHelp = false;
}

void StartMenu::Update()
{
	Window->clear();
	if (!m_showHelp)
	{
		Window->draw(*m_backgroundSprite);
		m_highscore->UpdateStartMenu();
	}
	else
	{
		Window->draw(*m_backgroundSprite);
	}
	if (m_keyboard.isKeyPressed(sf::Keyboard::Q) || m_keyboard.isKeyPressed(sf::Keyboard::U))
	{
		SetHelp(true);
	}
	Window->display();
}

void StartMenu::Cleanup()
{
	Clean(m_backgroundSprite);
	m_highscore->Cleanup();
	delete m_highscore;
}
bool StartMenu::GetHelp()
{
	return m_showHelp;
}
void StartMenu::SetHelp(bool help)
{
	m_showHelp = help;
	if (m_showHelp == true)
	{
		SetSprite(m_backgroundSprite,"Assets/GraphicalAssets/TempArt/how2.png");
	}
	else
	{
		SetSprite(m_backgroundSprite,"Assets/GraphicalAssets/TempArt/how.png");
	}
}
#pragma endregion