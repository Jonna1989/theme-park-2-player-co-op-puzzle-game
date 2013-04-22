#pragma once

#include <SFML/Graphics.hpp>
#include "FrameTime.h"
#include "WindowManager.h"
#include "TextureProvider.h"

const float PARTICLE_TIME = 2;

class Particle
{
public:
	Particle();
	~Particle();

	void Initialize(float rotation, float xPos, float yPos);
	void Update();
	void Cleanup();

	void StartParticle(float xPos, float yPos);

	bool IsBusy();
	sf::Sprite* GetSprite();


private:
	sf::Texture* m_texture;
	sf::Sprite* m_sprite;

	sf::Clock* m_clock;

	float m_alpha;
	float m_rotation;
	bool m_busy;

	float m_fly;
};

