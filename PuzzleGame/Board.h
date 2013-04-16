#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "WindowManager.h"
#include "Tile.h"
#include "TextureProvider.h"

static int BOARD_HEIGHT = 10;
static int BOARD_WIDTH	 = 15;
static unsigned int TILE_SIZE_X = 50;
static unsigned int TILE_SIZE_Y = 50;
static const std::string SHEET_PATH_GREEN = "Assets/GraphicalAssets/TempArt/ball1.png";
static const std::string SHEET_PATH_BLUE = "Assets/GraphicalAssets/TempArt/ball2.png";
static const std::string SHEET_PATH_PURPLE = "Assets/GraphicalAssets/TempArt/ball3.png";
static const std::string SHEET_PATH_RED = "Assets/GraphicalAssets/TempArt/ball4.png";
static const std::string SHEET_PATH_YELLOW = "Assets/GraphicalAssets/TempArt/ball5.png";

class Board
{
public:
	enum SPACE
	{
		EMPTY_SPACE, 
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

	static Board* Instance();

	void Initialize();
	void Update();
	void Cleanup();
	
	std::vector<std::vector<Tile>> GetBoard();
	Tile* GetTile(int x, int y);

	int GetColor(int x, int y);
	int GetOwner(int x, int y);

	void SetColor(int x, int y, int color);
	void SetOwner(int x, int y, int owner);

	bool IsTileVacant(int x, int y);
	void DropTile(int x, int y);
	int NrOfAdjacentSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfAdjacentSameColor(int x, int y);

	void PrintBoardToConsole();	

private:
	Board();
	~Board();
	
	static Board* m_instance;

	std::vector<std::vector<Tile>> m_board;
	std::vector<sf::Sprite*> m_sprites;

	void InitializeSprites();
	void CreateBoard();

	void DrawBoard();
	void DrawTile(int x, int y);
};

#endif