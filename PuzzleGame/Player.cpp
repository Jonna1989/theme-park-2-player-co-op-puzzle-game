#include "Player.h"

#pragma region Base
Player::Player()
{
}


Player::~Player()
{
}

void Player::Initialize(int owner)
{
	m_piece = new PlayerPiece();
	m_piece->Initialize(owner);

	m_score = 0;
}

void Player::Update()
{

}

void Player::Cleanup()
{

}

#pragma endregion

#pragma region Getters

PlayerPiece* Player::GetPlayerPiece()
{
	return m_piece;
}

int Player::GetScore()
{
	return m_score;
}

#pragma endregion

#pragma region Setters

void Player::addToScore(int score)
{
	m_score += score;
}

void Player::resetScore()
{
	m_score = 0;
}

void Player::setScore(int newScore)
{
	m_score = newScore;
}

#pragma endregion