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
	
	m_avatarTexture=(TextureProvider::Instance()->GetTexture(PATH_AVATAR_FOLDER+avatarName+PATH_ENDING));
	CreateSprite(m_avatarSprite,m_avatarTexture,avatarPositionX,avatarPositionY);
}
void Avatar::Update()
{
	Window->draw(*m_avatarSprite);
}
void Avatar::Cleanup()
{
	Clean(m_avatarTexture,m_avatarSprite);
}
#pragma endregion

#pragma region Privates 



#pragma endregion