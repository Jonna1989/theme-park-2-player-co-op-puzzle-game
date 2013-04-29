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
	
	if(owner == 10 || owner == 11)
	{
		m_nextPieceOnePosition.x = BOARD_OFFSET_X - 20 - TILE_SIZE_X;
		m_nextPieceOnePosition.y = BOARD_OFFSET_Y - 20 + TILE_SIZE_Y;
		m_nextPieceTwoPosition.x = BOARD_OFFSET_X - 20 - TILE_SIZE_X;
		m_nextPieceTwoPosition.y = BOARD_OFFSET_Y - 20;
	}
	else if(owner == 20 || owner == 21)
	{
		m_nextPieceOnePosition.x = (float)BOARD_OFFSET_X + 1240;
		m_nextPieceOnePosition.y = (float)BOARD_OFFSET_Y - 20 + TILE_SIZE_Y;
		m_nextPieceTwoPosition.x = (float)BOARD_OFFSET_X + 1240;
		m_nextPieceTwoPosition.y = (float)BOARD_OFFSET_Y - 20;
	}

	m_score = 0;
}

void Player::Update()
{
	DrawNextPiece();
}

void Player::Cleanup()
{
	m_piece->Cleanup();
	delete m_piece;
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
std::string Player::GetScoreAsString()
{
	std::string result;
	std::ostringstream convert;
	convert << m_score;
	result = convert.str();
	return result;
}
#pragma endregion

#pragma region Setters

void Player::AddToScore(int score)
{
	m_score += score;
}

void Player::ResetScore()
{
	m_score = 0;
}

void Player::SetScore(int newScore)
{
	m_score = newScore;
}

#pragma endregion

#pragma region Misc

void Player::DrawNextPiece()
{
	Board::Instance()->DrawNextPiece(m_nextPieceOnePosition, m_nextPieceTwoPosition, m_piece->GetNextColorPieceOne(), m_piece->GetNextColorPieceTwo());
}

#pragma endregion