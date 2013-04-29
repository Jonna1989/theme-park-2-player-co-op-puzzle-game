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

	int GetColorToRemove();

	void SetColorToRemove(int color);

private:
	int m_colorToRemove;
};

#endif