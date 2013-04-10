#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void Initialize(sf::RenderWindow* window);
	void Update();
	void Cleanup();
};

