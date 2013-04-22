#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "WindowManager.h"
#include "Tile.h"
#include "TextureProvider.h"
#include "ParticleEffect.h"

static int BOARD_HEIGHT = 14;
static int BOARD_WIDTH	= 20;
static unsigned int TILE_SIZE_X = 50;
static unsigned int TILE_SIZE_Y = 50;
static unsigned int BOARD_OFFSET_X = 460;
static unsigned int BOARD_OFFSET_Y = 140;
static const int NUMBER_OF_BUBBLES = 5;
static const std::string PATH_TO_BUBBLES = "Assets/GraphicalAssets/Bubbles/";
static unsigned int NUMBER_OF_PARTICLES = 13;

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

	//Only the tiles above, below, to the right and to the left. Doesn't count the tile making the call
	int NrOfAdjacentSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfAdjacentSameColor(int x, int y);
	
	//All connected tiles, branching out to tiles connected to other connected tiles. Doesn't count the original tile making the call
	int NrOfConnectedSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfConnectedSameColor(int x, int y);

	void PrintBoardToConsole();

	void CheckForMatch();
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

	sf::Clock* removalClock;

	std::vector<ParticleEffect*> m_particleEffects;

	std::vector<std::string> SHEET_PATH_TO_BUBBLES;

	sf::Texture* m_backgroundTexture;
	sf::Sprite* m_backgroundSprite;

	sf::Texture* m_plateTexture;
	sf::Sprite* m_plateSprite;
};

#endif