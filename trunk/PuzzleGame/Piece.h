#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>

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
	sf::Sprite* GetSprite();

	void SetValue(int value);
	void SetPosition(int posX, int posY);

private:
	int m_value;
	sf::Vector2i m_position;

	sf::Texture* m_pieceTexture;
	sf::Sprite* m_pieceSprite;
};

