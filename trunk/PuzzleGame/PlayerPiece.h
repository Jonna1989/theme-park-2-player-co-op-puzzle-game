#ifndef PLAYER_PIECE_H
#define PLAYER_PIECE_H

#include <iostream>

#include "FrameTime.h"
#include "Piece.h"
#include "Board.h"
#include "Soundeffects.h"

#define PlayRotateSound Soundeffects::Instance()->PlaySound(Soundeffects::UISOUND,5,DEFAULT_PITCH,100);

const int SPAWN_PLAYER_1X = 4;
const int SPAWN_PLAYER_2X = 14;
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

	void ConvertPieceToPassive();
};

#endif