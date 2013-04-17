#include "ParticleEffect.h"

#pragma region Base

ParticleEffect::ParticleEffect()
{
}


ParticleEffect::~ParticleEffect()
{
}

#pragma endregion

#pragma region Publics

void ParticleEffect::Initialize()
{
	srand((int)time(0));
	for (int i = 0; i < PARTICLE_COUNT ; i++)
	{
		Particle particle;
		m_particles.push_back(particle);
		m_particles[i].Initialize((float)(rand () % (300 + 300) - 300));
	}

	m_clock = new sf::Clock();
}

void ParticleEffect::Update()
{
	for (int i = 0; i < PARTICLE_COUNT ; i++)
	{
		if (m_particles[i].IsBusy())
		{
			m_particles[i].Update();
			Window->draw(*m_particles[i].GetSprite());
		}
	}
	if (m_clock->getElapsedTime().asMilliseconds() > 50)
	{
		for (int i = 0; i < PARTICLE_COUNT ; i++)
		{
			if (!m_particles[i].IsBusy())
			{
				m_particles[i].StartParticle();
				m_clock->restart();
				break;
			}
		}
	}
}

void ParticleEffect::Cleanup()
{
	for (int i = 0; i < PARTICLE_COUNT ; i++)
	{
		m_particles[i].Cleanup();
	}
	delete m_clock;
}

#pragma endregion