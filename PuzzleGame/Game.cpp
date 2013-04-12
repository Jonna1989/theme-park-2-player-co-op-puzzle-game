#include "Game.h"
#include "StateManager.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::Initialize()
{
	m_board = new Board();
	m_board->Initialize();
	m_input = new InputManager();
	m_input->Initialize(m_board);
}

void Game::Update()
{
	m_board->Update();
	m_input->Update(true,1);
}

void Game::Cleanup()
{
	m_input->Cleanup();
	delete m_input;
	m_board->Cleanup();
	delete m_board;
}