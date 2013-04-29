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

	int GetBlastRadius();

	void SetBlastRadius(int blastRadius);

private:
	int m_blastRadius;
};

#endif