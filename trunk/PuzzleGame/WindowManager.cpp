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
		m_window = new sf::RenderWindow();
		m_window->create(sf::VideoMode(1920, 1080), "Puzzle Prototype", sf::Style::Fullscreen);
		m_window->setMouseCursorVisible(false);
	}

	void WindowManager::Cleanup()
	{
		delete m_window;
	}

	sf::RenderWindow* WindowManager::GetWindow()
	{
		return m_window;
	}
		
#pragma endregion