#pragma once

#include <SFML/Graphics.hpp>
#define Window WindowManager::Instance()->GetWindow()
class WindowManager
{
private:
	WindowManager();
	~WindowManager();

	static WindowManager* m_instance;
	sf::RenderWindow* m_window;

public:
	static WindowManager* Instance();

	void Initialize();
	void Cleanup();

	sf::RenderWindow* GetWindow();
};
