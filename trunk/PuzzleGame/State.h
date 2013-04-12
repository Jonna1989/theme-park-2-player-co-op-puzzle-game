#ifndef STATE_H
#define STATE_H

#include <iostream>

class State
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Cleanup() = 0;
};

#endif