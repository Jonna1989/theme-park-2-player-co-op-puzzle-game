#include "Avatar.h"

#pragma region Base
Avatar::Avatar()
{
	m_avatarAnimation = nullptr;
	m_clock = nullptr;
	m_animationCount = NULL;
	m_animationDelay = NULL;
}
Avatar::~Avatar()
{
}
#pragma endregion

#pragma region Publics

void Avatar::Initialize(const std::string &avatarName, float avatarPositionX, float avatarPositionY, sf::Vector2f cellSize, sf::Vector2i startPlace, int cellCount, int cellPerRow, float fps, int animationDelay)
{
	m_avatarAnimation = new Animation();
	m_avatarAnimation->Initialize(PATH_AVATAR_FOLDER+avatarName+PATH_ENDING, cellSize, startPlace, cellCount, cellPerRow, fps);
	m_avatarAnimation->getSprite()->setPosition(avatarPositionX,avatarPositionY);

	m_clock = new sf::Clock();

	m_animationCount = 0;
	m_animationDelay = animationDelay;
}
void Avatar::Update()
{
	if (m_clock->getElapsedTime().asSeconds() > m_animationDelay && m_avatarAnimation->getCurrentCell() == 1 && m_animationCount > 10)
	{
		m_animationDelay = rand () % (10 - 5) + 5;
		m_animationCount = 0;
		m_clock->restart();
	}
	else if (m_clock->getElapsedTime().asSeconds() > m_animationDelay || m_avatarAnimation->getCurrentCell() != 1)
	{
		m_animationCount++;
		m_avatarAnimation->Update();
	}
	std::cout << m_avatarAnimation->getCurrentCell() << std::endl;
	Window->draw(*m_avatarAnimation->getSprite());
}
void Avatar::Cleanup()
{
	delete m_clock;
	delete m_avatarAnimation;
}
#pragma endregion

#pragma region Privates 



#pragma endregion