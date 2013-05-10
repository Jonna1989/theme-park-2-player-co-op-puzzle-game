#include "Particle.h"
#include <iostream>
#include <cmath>

#pragma region Base

Particle::Particle()
{
}


Particle::~Particle()
{
}

#pragma endregion

#pragma region Publics

void Particle::Initialize(float rotation, float xPos, float yPos)
{
	m_rotation = rotation;
	m_rotation = ((m_rotation * 180.0f) / 3.141592653589793238462643383279502884197169399375105820974944f) * -1.0f;

	m_texture = TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/TempArt/pixel.png");
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*m_texture);
	m_sprite->setRotation(m_rotation);
	m_sprite->setPosition(xPos,yPos);

	m_busy = false;

	m_alpha = 255;

	m_value = 0;

	m_clock = new sf::Clock();

	m_fly = 0;
}

void Particle::Update()
{
	float angleToRadians = (3.141592653589793238462643383279502884197169399375105820974944f / 180.0f) * (m_sprite->getRotation());

	m_fly += 6.0f * DeltaTime;

	float xDir = (cos(angleToRadians) * 150.0f * DeltaTime);
	float yDir = (sin(angleToRadians) * -150.0f * DeltaTime - m_fly);
	if (m_alpha - 300.0f * DeltaTime > 0)
	{
		m_alpha -= 300.0f * DeltaTime;
	}
	else
	{
		m_alpha = 0;
	}
	
	m_sprite->setColor(sf::Color(m_sprite->getColor().r,m_sprite->getColor().g,m_sprite->getColor().b,(sf::Uint8)m_alpha));

	m_sprite->move(xDir,yDir);
	if (m_clock->getElapsedTime().asMilliseconds() > 1000)
	{
		m_busy = false;
	}
}

void Particle::Cleanup()
{
	delete m_sprite;
	delete m_clock;
}

void Particle::StartParticle(float xPos, float yPos, int value)
{
	m_clock->restart();
	m_sprite->setPosition(xPos,yPos);
	m_alpha = 255;
	m_value = value;
	m_fly = 0;
	m_busy = true;
}

bool Particle::IsBusy()
{
	return m_busy;
}

sf::Sprite* Particle::GetSprite()
{
	m_sprite->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Particles/particle0"+ConvertIntToStdString(m_value)+".png"));
	return m_sprite;
}

#pragma endregion