#include "FrameTime.h"


#pragma region base

FrameTime::FrameTime()
{
}


FrameTime::~FrameTime()
{
}

#pragma endregion

#pragma region Statics

FrameTime* FrameTime::m_instance = 0;

FrameTime* FrameTime::Instance()
{
	if (m_instance == 0)
	{
		m_instance = new FrameTime();
	}
	return m_instance;

}

void FrameTime::Initialize()
{
	m_clock = new sf::Clock();
	m_delta = 0.0f;
}

void FrameTime::Update()
{
	m_deltatime = m_clock->restart();
	m_delta = m_deltatime.asSeconds();
}

void FrameTime::Cleanup()
{
	delete m_clock;
}

float FrameTime::GetDelta()
{
	return m_delta;
}

#pragma endregion