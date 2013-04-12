#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include "PlayerPiece.h"
#include "WindowManager.h"

static unsigned int BOARD_HEIGHT = 10;
static unsigned int BOARD_WIDTH	 = 15;


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
		PLAYER_ONE	= 10,
		PLAYER_TWO	= 20,
		
	};
	void Initialize();
	void Update();
	void Cleanup();

	PlayerPiece* GetPlayerPiece();
private:
	std::vector< std::vector<sf::Vector2i>* >* m_Board2dVector;
	void CreateBoard();
	void PrintBoardToConsole();
#pragma region KeyCommands
	void KeyCommands();
	void KeyCommand_PrintBoardToConsole();
	void KeyCommand_DropNewPiece();
	void KeyCommand_ClearBottomRow();
#pragma endregion
	void DropPiece();
	void AddPlayer1PieceTo2dVector();
	void Gravity();
	void UseTimedFunctions();
	int	 GetBoardVector(int y, int x);
	void SetBoardVector(int y, int x, int newValue);
	sf::Vector2i VectorFill;
	sf::Clock*	GravityClock;
	sf::Time*   GravityTime;
	int			GravityInterval;

	PlayerPiece* m_playerPiece;

	

};

