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

	void StartParticle(float xPos, float yPos, int value);

	bool IsBusy();
	sf::Sprite* GetSprite();


private:
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;

	int m_value;
	float m_alpha;
	float m_rotation;
	bool m_busy;

	float m_fly;
};

