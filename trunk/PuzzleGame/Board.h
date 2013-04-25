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

static int BOARD_HEIGHT = 10;
static int BOARD_WIDTH	= 16;
static unsigned int TILE_SIZE_X = 75;
static unsigned int TILE_SIZE_Y = 75;
static unsigned int BOARD_OFFSET_X = 460;
static unsigned int BOARD_OFFSET_Y = 140;
static const int NUMBER_OF_BUBBLES = 5;
static const std::string PATH_TO_BUBBLES = "Assets/GraphicalAssets/Bubbles/";
static const std::string PATH_LEVEL_1 = "Assets/Levels/Level1.txt";
static const std::string PATH_LEVEL_2 = "Assets/Levels/Level2.txt";
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

	void SetBoard(int level);
	
	std::vector<std::vector<Tile>> GetBoard();
	Tile* GetTile(int x, int y);

	int GetColor(int x, int y);
	int GetOwner(int x, int y);

	bool GetPlayer1HalfStep();
	bool GetPlayer2HalfStep();

	void SetColor(int x, int y, int color);
	void SetOwner(int x, int y, int owner);

	void SetBoardHalfStep(int halfStep);
	void SetPlayer1HalfStep(int halfStep);
	void SetPlayer2HalfStep(int halfStep);

	bool IsTileVacant(int x, int y);
	void DropTile(int x, int y);

	//Only the tiles above, below, to the right and to the left
	int NrOfAdjacentSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfAdjacentSameColor(int x, int y);
	
	//All connected tiles, branching out to tiles connected to other connected tiles
	int NrOfConnectedSameColor(int x, int y);
	std::vector<sf::Vector2i> PositionsOfConnectedSameColor(int x, int y);

	void PrintBoardToConsole();

	void CheckForMatch();

	void CheckForFall(int x, int y);

	// Returns the first tile found with the specified owner
	Tile* GetSpecifiedTile(int owner);

private:
	Board();
	~Board();
	
	static Board* m_instance;

	std::vector<std::vector<Tile>> m_board;
	std::vector<sf::Sprite*> m_sprites;

	sf::Clock* soundClock;

	std::vector<ParticleEffect*> m_particleEffects;
	std::vector<std::vector<int>> m_levels;

	std::vector<std::string> SHEET_PATH_TO_BUBBLES;

	sf::Texture* m_backgroundTexture;
	sf::Sprite* m_backgroundSprite;

	sf::Texture* m_plateTexture;
	sf::Sprite* m_plateSprite;

	int m_player1HalfStep;
	int m_player2HalfStep;
	void PlayComboSound(sf::Clock* &comboClock);
	float m_comboVolume;
	float m_comboPitch;
	int   m_comboSoundThreshold;

	void InitializeSprites();
	void InitializeLevels();
	void ReadTextLevels(std::string sheetPath);
	void CreateBoard();

	void DrawBoard();
	void DrawTile(int x, int y);

	Score* m_score;
};

#endif