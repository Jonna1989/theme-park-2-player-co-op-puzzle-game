#include "WindowManager.h"

#pragma region Base

WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

#pragma endregion

#pragma region Static

WindowManager* WindowManager::m_instance = 0;

WindowManager* WindowManager::Instance()
{
	if(m_instance == 0)
	{
		m_instance = new WindowManager();
	}
	return m_instance;
}

#pragma endregion

#pragma region Publics

void WindowManager::Initialize()
{
	m_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pop!", sf::Style::Fullscreen);
	m_window->setMouseCursorVisible(true);
	m_window->setFramerateLimit(60);
}

void WindowManager::Cleanup()
{
	delete m_window;
	delete m_instance;
}

sf::RenderWindow* WindowManager::GetWindow()
{
	return m_window;
}
		
#pragma endregion