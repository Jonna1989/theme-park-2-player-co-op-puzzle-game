#include "ParticleEffect.h"

#pragma region Base

ParticleEffect::ParticleEffect()
{
	m_clock = nullptr;

	m_version = NULL;

	m_xPos = NULL;
	m_yPos = NULL;

	m_isBusy = NULL;
}


ParticleEffect::~ParticleEffect()
{
}

#pragma endregion

#pragma region Publics

void ParticleEffect::Initialize()
{
	for (int i = 0; i < PARTICLE_COUNT ; i++)
	{
		Particle particle;
		m_particles.push_back(particle);
		m_particles[i].Initialize((float)(rand () % (300 + 300) - 300), m_xPos, m_yPos);
	}

	m_clock = new sf::Clock();
	m_xPos = 0;
	m_yPos = 0;
	m_version = 0;
	m_isBusy = false;
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
	if (!m_particles[7].IsBusy())
	{
		m_isBusy = false;
	}
}

void ParticleEffect::Cleanup()
{
	for (int i = 0; i < PARTICLE_COUNT ; i++)
	{
		m_particles[i].Cleanup();
	}
	m_particles.clear();

	delete m_clock;
}

void ParticleEffect::StartEffect(float xPos, float yPos, int value, int version)
{
	m_clock->restart();
	m_version = version;
	m_xPos = xPos;
	m_yPos = yPos;
	for (int i = 0; i < PARTICLE_COUNT; i++)
	{
		if (m_version == 1)
		{
			m_particles[i].StartParticle(m_xPos, m_yPos, value, (float)((rand () % (20 - 1) + 5)/10), m_version);
		}
		else if (m_version == 2)
		{
			std::cout << value << std::endl;
			if (i < PARTICLE_COUNT/2)
			{
				m_particles[i].StartParticle(m_xPos, m_yPos, RandomNumber(101,107), (float)((rand () % (20 - 1) + 5)/10), m_version);
			}
			else
			{
				m_particles[i].StartParticle(m_xPos, m_yPos, value, (float)((rand () % (20 - 1) + 5)/10), m_version);
			}
		}
	}
	m_isBusy = true;
}

bool ParticleEffect::IsBusy()
{
	return m_isBusy;
}

#pragma endregion