#pragma once

#include <SFML/Graphics.hpp>
#include "FrameTime.h"
#include "WindowManager.h"
#include "TextureProvider.h"
#include "Load.h"

const float PARTICLE_TIME = 2;

class Particle
{
public:
	Particle();
	~Particle();

	void Initialize(float rotation, float xPos, float yPos);
	void Update();
	void Cleanup();

	void StartParticle(float xPos, float yPos, int value, float scale, int version);

	bool IsBusy();
	sf::Sprite* GetSprite();

	enum
	{
		NOTHING,
		NORMAL,
		FRIEND
	};

private:
	sf::Sprite* m_sprite;

	float m_scale;
	int m_value;
	float m_alpha;
	float m_rotation;
	bool m_busy;
	int m_version;

	float m_fly;
};

