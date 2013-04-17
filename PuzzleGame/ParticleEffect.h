#pragma once

#include "Particle.h"
#include <vector>

const int PARTICLE_COUNT = 100;

class ParticleEffect
{
public:
	ParticleEffect();
	~ParticleEffect();

	void Initialize();
	void Update();
	void Cleanup();

private:
	std::vector<Particle> m_particles;

	sf::Clock* m_clock;
};

