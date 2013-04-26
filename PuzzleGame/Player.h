#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerPiece.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize(int owner);
	void Update();
	void Cleanup();

	PlayerPiece* GetPlayerPiece();
	int GetScore();
	std::string GetScoreAsString();
	void AddToScore(int score);
	void ResetScore();
	void SetScore(int newScore);

	void DrawNextPiece();

private:
	PlayerPiece* m_piece;
	sf::Vector2f m_nextPieceOnePosition;
	sf::Vector2f m_nextPieceTwoPosition;

	int m_score;
};

#endif