#pragma once

#include "Piece.h"

class PlayerPiece
{
public:
	PlayerPiece();
	~PlayerPiece();

	void Initialize();
	void Update();
	void Cleanup();

	void RotateBlock(int dir);

	void MoveBlock();

	void SetPieces(int valueOne,int valueTwo);

	Piece* GetPieceOne();
	Piece* GetPieceTwo();

private:
	Piece* m_pieceOne;
	Piece* m_pieceTwo;
};

