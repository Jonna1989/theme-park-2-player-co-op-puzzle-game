#pragma once

#include <SFML/Graphics.hpp>

class Piece
{
public:
	Piece();
	~Piece();

	void Initialize();
	void Update();
	void Cleanup();

	int GetValue();
	sf::Vector2i GetPosition();

	void SetValue(int value);
	void SetPosition(int posX, int posY);

private:
	int m_value;
	sf::Vector2i m_position;
};

