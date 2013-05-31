#pragma once

#include "Particle.h"
#include <vector>
#include "Load.h"

const int PARTICLE_COUNT = 8;

class ParticleEffect
{
public:
	ParticleEffect();
	~ParticleEffect();

	void Initialize();
	void Update();
	void Cleanup();

	void StartEffect(float xPos, float yPos, int value, int version);

	bool IsBusy();

private:
	std::vector<Particle> m_particles;

	sf::Clock* m_clock;

	int m_version;

	float m_xPos;
	float m_yPos;

	bool m_isBusy;
};

