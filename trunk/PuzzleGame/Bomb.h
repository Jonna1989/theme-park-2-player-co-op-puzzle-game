#ifndef BOMB_H
#define BOMB_H

#include "PowerItem.h"

class Bomb : public PowerItem
{
public:
	Bomb();
	~Bomb();

	void Initialize();
	void Update();
	void Cleanup();

	void Activate();

	sf::Vector2i GetPosition();
	void SetPosition(int x, int y);

	bool IsFalling();
	void SetFalling(bool falling);

private:
	int m_blastRadius;
};

#endif