#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "PlayerPiece.h"
#include "WindowManager.h"
#include "Load.h"

static unsigned int BOARD_HEIGHT = 10;
static unsigned int BOARD_WIDTH	 = 20;
class Board
{
public:
	Board();
	~Board();
	enum SPACE
	{
		EMPTY_SPACE = 0, 
		GREEN_SPACE, 
		BLUE_SPACE, 
		PURPLE_SPACE, 
		RED_SPACE, 
		YELLOW_SPACE 
	};
	enum PLAYER
	{
		PASSIVE		= 0,
		PLAYER_ONE_PIECE_ONE	= 10,
		PLAYER_ONE_PIECE_TWO	= 11,
		PLAYER_TWO	= 20,
		
	};
	void Initialize();
	void Update();
	void Cleanup();
	int	 GetBoardVectorX(int y, int x);
	int	 GetBoardVectorY(int y, int x);
	PlayerPiece* GetPlayerPiece();
	bool IsTileVacant(int x, int y);

private:
	std::vector< std::vector<sf::Vector2i>* >* m_Board2dVector;
	void CreateBoard();
	void PrintBoardToConsole();
	void PrintPlayerOnePlayerPiecePositionsToConsole();
#pragma region KeyCommands
	void KeyCommands();
	void KeyCommand_PrintBoardToConsole();
	void KeyCommand_DropNewPiece();
	void KeyCommand_ClearBottomRow();
#pragma endregion All the KeyCommands
	void DropPiece();
	void AddPlayer1PieceTo2dVector();
	void Gravity();
	void UpdatePlayer1PlayerPiece();
	void UpdatePlayer1VectorPos();
	void SpaceDrawer();
//	void CheckIf
	void UseTimedFunctions();
	void SetBoardVectorX(int y, int x, int newValue);
	void SetBoardVectorY(int y, int x, int newValue);
	sf::Vector2i VectorFill;
	sf::Clock*	GravityClock;
	sf::Time*   GravityTime;
	int			GravityInterval;
	sf::Texture* m_green;
	sf::Texture* m_blue;
	sf::Texture* m_purple;
	sf::Texture* m_red;
	sf::Texture* m_yellow;
	sf::Sprite*  m_pieceSprite;
	PlayerPiece* m_playerPiece;
	
	

};

#endif