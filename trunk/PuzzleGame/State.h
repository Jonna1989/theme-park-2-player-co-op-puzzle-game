#pragma once

#include <iostream>

class State
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Cleanup() = 0;
};