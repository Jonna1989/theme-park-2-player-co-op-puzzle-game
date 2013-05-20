#ifndef THORN_H
#define THORN_H

#include "PowerItem.h"

class Thorn : public PowerItem
{
public:
	Thorn();
	~Thorn();

	void Initialize();
	void Update();
	void Cleanup();

	void Activate();
	void Drop();
};

#endif