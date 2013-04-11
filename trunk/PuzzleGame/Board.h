#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include "PlayerPiece.h"
#include "WindowManager.h"

static unsigned int BOARD_HEIGHT = 15;
static unsigned int BOARD_WIDTH	 = 10;


class Board
{
public:
	Board();
	~Board();
	enum SPACE
	{
		EMPTY_SPACE, 
		GREEN_SPACE, 
		BLUE_SPACE, 
		PURPLE_SPACE, 
		RED_SPACE, 
		YELLOW_SPACE 
	};

	void Initialize();
	void Update();
	void Cleanup();

	PlayerPiece* GetPlayerPiece();

private:
	std::vector< std::vector<int>* >* m_Board2dVector;
	void CreateBoard();
	void PrintBoardToConsole();
	void KeyCommand_PrintBoardToConsole();
	void DropPiece();
	void AddPlayer1PieceTo2dVector();
	void Gravity();
	void UseTimedFunctions();
	sf::Clock* GravityClock;
	sf::Time*   GravityTime;
	PlayerPiece* m_playerPiece;

	

};

