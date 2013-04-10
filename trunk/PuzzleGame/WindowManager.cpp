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
		m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Saints Tears");
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