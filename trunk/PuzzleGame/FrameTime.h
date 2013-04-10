#pragma once

#include <SFML/Graphics.hpp>
#define DeltaTime FrameTime::Instance()->GetDelta()

class FrameTime
{
public:
	static FrameTime* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	float GetDelta();

private:
	FrameTime();
	~FrameTime();

	static FrameTime* m_instance;

	sf::Clock* m_clock;
	sf::Time m_deltatime;
	float m_delta;
};

