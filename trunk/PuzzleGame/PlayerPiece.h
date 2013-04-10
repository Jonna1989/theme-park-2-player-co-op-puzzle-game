#pragma once

#include "Piece.h"
#include "FrameTime.h"
#include <iostream>
class PlayerPiece
{
public:
	PlayerPiece();
	~PlayerPiece();

	void Initialize();
	void Update();
	void Cleanup();

	void RotatePiece(int dir);

	void MovePiece();

	void SetPieces(int valueOne,int valueTwo);

	Piece* GetPieceOne();
	Piece* GetPieceTwo();

private:
	Piece* m_pieceOne;
	Piece* m_pieceTwo;
};

