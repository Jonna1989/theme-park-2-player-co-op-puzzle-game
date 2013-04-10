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
	m_board = new Board;
	m_board->Initialize();
}

void Game::Update()
{
	m_board->Update();
}

void Game::Cleanup()
{

}