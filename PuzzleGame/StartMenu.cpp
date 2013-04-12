#include "StartMenu.h"
#include "StateManager.h"

#pragma region Base

StartMenu::StartMenu()
{
}


StartMenu::~StartMenu()
{
}

#pragma endregion

#pragma region Publics

void StartMenu::Initialize()
{
	m_backgroundTexture = new sf::Texture();
	m_backgroundSprite = new sf::Sprite();
	m_backgroundTexture->loadFromFile("Assets/GraphicalAssets/TempArt/menu.png");
	m_backgroundSprite->setTexture(*m_backgroundTexture);

	m_input = new InputManager();
	m_input->Initialize();
}

void StartMenu::Update()
{
	Window->clear();
	Window->draw(*m_backgroundSprite);
	Window->display();

	m_input->Update(true,0);
}

void StartMenu::Cleanup()
{
	m_input->Cleanup();
	delete m_input;
}

#pragma endregion