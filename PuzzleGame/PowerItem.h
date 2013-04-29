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
	virtual void Update() = 0;
	virtual void Cleanup() = 0;

	virtual void Activate() = 0;
	virtual void Drop();

	virtual sf::Vector2i GetPosition();
	virtual bool IsFalling();
	virtual bool IsGoodItem();

	virtual void SetPosition(int x, int y);
	virtual void SetFalling(bool falling);
	virtual void SetGoodItem(bool good);

protected:
	sf::Vector2i m_position;
	bool m_isFalling;
	bool m_goodItem; //true = powerup, false = trap
};

#endif