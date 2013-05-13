#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include <iostream>

#include "FrameTime.h"
#include "Piece.h"
#include "Board.h"
#include "Soundeffects.h"

const int SPAWN_PLAYER_1X = BOARD_WIDTH/2-(BOARD_WIDTH/3);
const int SPAWN_PLAYER_2X = BOARD_WIDTH/2+(BOARD_WIDTH/3)-1;
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
	int GetNextColorPieceOne();
	int GetNextColorPieceTwo();
	sf::Vector2i GetPositionPieceOne();
	sf::Vector2i GetPositionPieceTwo();
	int GetOwner();
	sf::Vector2i GetSpawnPointOne();
	sf::Vector2i GetSpawnPointTwo();

	void SetColors(int colorOne,int colorTwo);
	void SetPositions(int oneX, int oneY, int twoX, int twoY);
	void SetOwner(int owner);
	void SetPositionToSpawn();
	void SetSpawnPointOne(int x, int y);
	void SetSpawnPointTwo(int x, int y);

	void SetNewPlayerPieces();

private:
	Piece* m_pieceOne;
	Piece* m_pieceTwo;
	int m_owner;
	sf::Vector2i m_spawnPointOne; //For piece one
	sf::Vector2i m_spawnPointTwo; //For piece two
	int m_pieceOneNextColor;
	int m_pieceTwoNextColor;

	void ConvertPieceToPassive();
};

#endif