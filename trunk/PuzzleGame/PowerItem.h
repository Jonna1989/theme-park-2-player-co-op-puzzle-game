#ifndef POWER_ITEM_H
#define POWER_ITEM_H

#include <SFML/Graphics.hpp>

#include "Board.h"

class PowerItem
{
public:
	PowerItem();
	~PowerItem();

	virtual void Initialize() = 0;
	virtual void Upddate() = 0;
	virtual void Cleanup() = 0;

	virtual void Activate() = 0;

	virtual sf::Vector2i GetPosition() = 0;
	virtual bool IsFalling() = 0;

	virtual void SetPosition(int x, int y) = 0;
	virtual void SetFalling(bool falling) = 0;

protected:
	sf::Vector2i m_position;
	bool m_isFalling;
};

#endif