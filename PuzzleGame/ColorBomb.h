#ifndef COLOR_BOMB_H
#define COLOR_BOMB_H

#include "PowerItem.h"

class ColorBomb : public PowerItem
{
public:
	ColorBomb();
	~ColorBomb();

	void Initialize();
	void Update();
	void Cleanup();

	void Activate();

	sf::Vector2i GetPosition();
	bool IsFalling();
	int GetColorToRemove();
	
	void SetPosition(int x, int y);
	void SetFalling(bool falling);
	void SetColorToRemove(int color);

private:
	int m_colorToRemove;
};

#endif