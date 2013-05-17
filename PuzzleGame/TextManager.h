#pragma once
#include "Load.h"
#include "WindowManager.h"
class TextManager
{
public:
	TextManager();
	~TextManager();


	void Initialize(unsigned int numberOfCharsToEnter, unsigned int numberOfLetters);
	void Update();
	void Cleanup();

private:
	std::vector<std::vector<int>> m_textNumbers;
	int m_position;
	int m_char;
};

