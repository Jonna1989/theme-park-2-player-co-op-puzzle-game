#include "SetTeamName.h"


SetTeamName::SetTeamName(void)
{
}


SetTeamName::~SetTeamName(void)
{
}
void SetTeamName::Initialize()
{
	TextManager::Instance()->Initialize(3,3,500,500);
}
void SetTeamName::Update()
{
	Window->clear();
	TextManager::Instance()->Update();
	Window->display();
}
void SetTeamName::Cleanup()
{

}