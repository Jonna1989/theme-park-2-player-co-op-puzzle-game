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

void Avatar::Initialize(const std::string &avatarName, float avatarPositionX, float avatarPositionY, sf::Vector2f cellSize, sf::Vector2i startPlace, int cellCount, int cellPerRow, float fps, int animationDelay, int player)
{
	m_avatarAnimation = new Animation();
	m_avatarAnimation->Initialize(PATH_AVATAR_FOLDER+avatarName+PATH_ENDING, cellSize, startPlace, cellCount, cellPerRow, fps);
	m_avatarAnimation->getSprite()->setPosition(avatarPositionX,avatarPositionY);

	m_clock = new sf::Clock();
	m_expressionClock = new sf::Clock();

	m_sprite = new sf::Sprite();
	m_sprite->setPosition(avatarPositionX,avatarPositionY);

	m_player = player;

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


	if (m_player == 1)
	{
		if (m_expressionClock->getElapsedTime().asSeconds() > 1 && m_expressionActive)
		{
			m_expressionActive = false;
			Board::Instance()->SetHappyP1(false);
			Board::Instance()->SetSadP1(false);
		}
		if (Board::Instance()->IsPlayer1Happy())
		{
			StartHappy();
			TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(640/2,523),"Assets/GraphicalAssets/Avatars/lily_reactions.png",m_sprite);
			Window->draw(*m_sprite);
		}
		else if (Board::Instance()->IsPlayer1Sad())
		{
			StartSad();
			Window->draw(*m_sprite);
		}
		else
		{
			Window->draw(*m_avatarAnimation->getSprite());
		}
	}
	else if (m_player == 2)
	{
		if (m_expressionClock->getElapsedTime().asSeconds() > 1 && m_expressionActive)
		{
			m_expressionActive = false;
			Board::Instance()->SetHappyP2(false);
			Board::Instance()->SetSadP2(false);
		}
		if (Board::Instance()->IsPlayer2Happy())
		{
			StartHappy();
			Window->draw(*m_sprite);
		}
		else if (Board::Instance()->IsPlayer2Sad())
		{
			StartSad();
			Window->draw(*m_sprite);
		}
		else
		{
			Window->draw(*m_avatarAnimation->getSprite());
		}
	}
}

void Avatar::Cleanup()
{
	delete m_clock;
	delete m_expressionClock;
	delete m_avatarAnimation;
	delete m_sprite;
}

void Avatar::StartHappy()
{
	if (m_player == 1)
	{
		TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(640/2,523),"Assets/GraphicalAssets/Avatars/lily_reactions.png",m_sprite);
	}
	else if (m_player == 2)
	{
		TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(554/2,534),"Assets/GraphicalAssets/Avatars/rose_reactions.png",m_sprite);
	}
	if (!m_expressionActive)
	{
		m_expressionActive = true;
		m_expressionClock->restart();
	}
}

void Avatar::StartSad()
{
	if (m_player == 1)
	{
		TextureProvider::Instance()->GetSubRect(sf::Vector2i(640/2,0),sf::Vector2i(640/2,523),"Assets/GraphicalAssets/Avatars/lily_reactions.png",m_sprite);
	}
	else if (m_player == 2)
	{
		TextureProvider::Instance()->GetSubRect(sf::Vector2i(554/2,0),sf::Vector2i(554/2,534),"Assets/GraphicalAssets/Avatars/rose_reactions.png",m_sprite);
	}
}

#pragma endregion

#pragma region Privates 



#pragma endregion