#pragma once

#include "Game.h"

class Base
{
public:
	Base();

	void Initialize();
	void Update();
	void Cleanup();

private:
	sf::RenderWindow* m_window;

	sf::Texture* m_loadingTexture;
	sf::Sprite* m_loadingSprite;

	Game* m_game;
};
