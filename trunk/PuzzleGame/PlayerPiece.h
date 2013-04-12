#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include "Piece.h"
#include "FrameTime.h"
#include <iostream>
class PlayerPiece
{
public:
	PlayerPiece();
	~PlayerPiece();

	void Initialize(int boardHeight, int boardWidth);
	void Update();
	void Cleanup();

	void RotatePiece(int dir);
	void MovePiece(int xDirection);
	void DropPiece();

	void SetPieces(int valueOne,int valueTwo);

	Piece* GetPieceOne();
	Piece* GetPieceTwo();

private:
	Piece* m_pieceOne;
	Piece* m_pieceTwo;

	int m_boardHeight;
	int m_boardWidth;
};

#endif