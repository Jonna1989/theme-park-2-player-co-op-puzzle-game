#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include "PlayerPiece.h"
#include "WindowManager.h"
static unsigned int BOARD_HEIGHT = 20;
static unsigned int BOARD_WIDTH	 = 20;
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

private:
	std::vector< std::vector<int>* >* m_Board2dVector;
	void CreateBoard();
	void PrintBoardToConsole();
	void DropPiece();
	void SetPlayerPieceTo2dVector();
	PlayerPiece* m_playerPiece;

	

};

