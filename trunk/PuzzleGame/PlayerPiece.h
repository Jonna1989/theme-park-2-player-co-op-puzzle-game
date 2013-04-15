#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include <iostream>

#include "FrameTime.h"
#include "Piece.h"
#include "Board.h"

class PlayerPiece
{
public:
	PlayerPiece();
	~PlayerPiece();

	void Initialize(int owner);
	void Update();
	void Cleanup();

	void RotatePiece(int dir);
	void MovePiece(int xDirection);
	bool DropPiece();
	void DropPieceQuickly();
	void RandomizeNewPiece();

	Piece* GetPieceOne();
	Piece* GetPieceTwo();

	int GetColorPieceOne();
	int GetColorPieceTwo();
	sf::Vector2i GetPositionPieceOne();
	sf::Vector2i GetPositionPieceTwo();
	int GetOwner();

	void SetColors(int colorOne,int colorTwo);
	void SetPositions(int oneX, int oneY, int twoX, int twoY);
	void SetOwner(int owner);

private:
	Piece* m_pieceOne;
	Piece* m_pieceTwo;
	int m_owner;

	Board* m_board;
};

#endif