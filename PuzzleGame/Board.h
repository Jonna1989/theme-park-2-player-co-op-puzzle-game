#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

#include "WindowManager.h"
#include "Tile.h"
#include "TextureProvider.h"
#include "ParticleEffect.h"
#include "Soundeffects.h"
#include "Score.h"
#include "Load.h"
#include "Animation.h"

static int BOARD_HEIGHT = 14;
static int BOARD_WIDTH	= 14;

static unsigned int TILE_SIZE_X = 75;
static unsigned int TILE_SIZE_Y = 75;

static unsigned int BOARD_OFFSET_X = 435;
static int BOARD_OFFSET_Y = -100;

static const int NUMBER_OF_BUBBLES = 7;
static const int NUMBER_OF_POWERITEMS = 3;
static const int NUMBER_OF_MISC_SPRITES = 4;

static const std::string PATH_TO_BUBBLES = "Assets/GraphicalAssets/Bubbles/";

static const std::string PATH_LEVEL_1 = "Assets/Levels/Level1.txt";
static const std::string PATH_LEVEL_2 = "Assets/Levels/Level2.txt";
static const std::string PATH_LEVEL_3 = "Assets/Levels/Level3.txt";
static const std::string PATH_LEVEL_4 = "Assets/Levels/Level4.txt";

static unsigned int NUMBER_OF_PARTICLES = 20;

class Board
{
public:
	enum SPACE
	{
		EMPTY_SPACE, 
		BLUE_SPACE, 
		GREEN_SPACE, 
		PURPLE_SPACE,
		RED_SPACE, 
		YELLOW_SPACE,
		ORANGE_SPACE,
		CYAN_SPACE
	};

	enum PLAYER
	{
		PASSIVE		= 0,
		PLAYER_ONE	= 10,
		PLAYER_TWO	= 20
	};

	enum SPRITEINDEX
	{
		BLUE_INDEX, //Bubbles, 0
		GREEN_INDEX,
		PURPLE_INDEX,
		RED_INDEX,
		YELLOW_INDEX,
		ORANGE_INDEX,
		CYAN_INDEX,
		CHESTNUT_INDEX, //PowerItems, 7
		MUSHROOM_INDEX,
		THORN_INDEX,
		AURA1_INDEX, //Auras, 10
		AURA2_INDEX,
		AURA1_TRANSPARENT_INDEX,
		AURA2_TRANSPARENT_INDEX
	};

	static Board* Instance();

	void Initialize();
	void Update();
	void Cleanup();

	void DeleteBoardInstance();
	void SetBoard(int level);
	std::vector<std::vector<Tile>> GetBoard();
	std::vector<std::string> GetBubblesSheetpaths();
	std::vector<sf::Sprite*> GetSprites();
	Tile* GetTile(int x, int y);
	Tile* GetSpecifiedTile(int owner); // Returns the first tile found with the specified owner

	int GetColor(int x, int y);
	int GetOwner(int x, int y);
	int GetPreviousOwner(int x, int y);

	bool GetPlayer1HalfStep();
	bool GetPlayer2HalfStep();

	void SetColor(int x, int y, int color);
	void SetOwner(int x, int y, int owner);
	void SetPreviousOwner(int x, int y, int previousOwner);

	void SetBoardHalfStep(int halfStep);
	void SetPlayer1HalfStep(int halfStep);
	void SetPlayer2HalfStep(int halfStep);

	bool IsTileVacant(int x, int y);
	void DropTile(int x, int y);
	bool IsTilePowerItem(int x, int y);

	//Only the tiles above, below, to the right and to the left
	int NrOfAdjacentSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfAdjacentSameColor(int x, int y);
	
	//All connected tiles, branching out to tiles connected to other connected tiles
	int NrOfConnectedSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfConnectedSameColor(int x, int y);

	void CheckForMatch();
	void CheckForFall(int x, int y);

	void CheckForGameOver();

	void DrawNextPiece(sf::Vector2f positionOne, sf::Vector2f positionTwo, int colorOne, int colorTwo);

	void PrintBoardToConsole();
	
	void SetFallPositionP1(int pos);
	void SetFallPositionP2(int pos);

private:
	Board();
	~Board();
	
	static Board* m_instance;

	std::vector<std::vector<Tile>> m_board;
	std::vector<sf::Sprite*> m_sprites;

	sf::Clock* soundClock;

	std::vector<ParticleEffect*> m_particleEffects;
	std::vector<std::vector<int>> m_levels;
	std::vector<std::string> bubblesSheetpaths;
	
	Animation* m_glowAnimation;
	
	Score* m_score;
	
	sf::Sprite* m_backgroundSprite;

	sf::Sprite* m_plateSprite;

	sf::Sprite* m_frameSprite;

	sf::Sprite* m_newPieceSpawnSprite;

	int m_player1HalfStep;
	int m_player2HalfStep;
	float m_comboVolume;
	float m_comboPitch; 
	int   m_comboSoundThreshold;

	void InitializeSprites();
	void InitializeLevels();
	void ReadTextLevels(std::string sheetPath);
	void CreateBoard();

	void DrawBoard();
	void DrawTile(int x, int y);
	void DrawGlow();
	void DrawNewPieceSpawn();
	void PlayComboSound(sf::Clock* &comboClock);

	Animation* m_fallGlowAnimationP1;
	Animation* m_fallGlowAnimationP2;
	int m_fallPosP1;
	int m_fallPosP2;
};

#endif