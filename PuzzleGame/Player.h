#ifndef PLAYER_H
#define PLAYER_H

#include <iomanip>
#include <locale>
#include <sstream>

#include "Board.h"
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
	void addToScore(int score);
	void resetScore();
	void setScore(int newScore);

private:
	PlayerPiece* m_piece;

	int m_score;
};

#endif