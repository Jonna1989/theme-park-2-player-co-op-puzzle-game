#include "Avatar.h"

#pragma region Base
Avatar::Avatar()
{
}
Avatar::~Avatar()
{
}
#pragma endregion

#pragma region Publics

void Avatar::Initialize(const std::string avatarName, float avatarPositionX, float avatarPositionY)
{
	m_avatarAnimation = new Animation();
	m_avatarAnimation->Initialize(PATH_AVATAR_FOLDER+avatarName+PATH_ENDING,sf::Vector2f(106,100),sf::Vector2i(0,0),5,5,0.5);
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