#include "Avatar.h"

#pragma region Base
Avatar::Avatar()
{
	m_avatarAnimation = nullptr;
}
Avatar::~Avatar()
{
}
#pragma endregion

#pragma region Publics

void Avatar::Initialize(const std::string &avatarName, float avatarPositionX, float avatarPositionY, sf::Vector2f cellSize, sf::Vector2i startPlace, int cellCount, int cellPerRow, float fps)
{
	m_avatarAnimation = new Animation();
	m_avatarAnimation->Initialize(PATH_AVATAR_FOLDER+avatarName+PATH_ENDING, cellSize, startPlace, cellCount, cellPerRow, fps);
	m_avatarAnimation->getSprite()->setPosition(avatarPositionX,avatarPositionY);
}
void Avatar::Update()
{
	m_avatarAnimation->Update();
	Window->draw(*m_avatarAnimation->getSprite());
}
void Avatar::Cleanup()
{
	delete m_avatarAnimation;
}
#pragma endregion

#pragma region Privates 



#pragma endregion