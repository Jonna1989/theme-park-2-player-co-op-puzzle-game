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

static int BOARD_HEIGHT = 12;
static int BOARD_WIDTH	= 16;
static unsigned int TILE_SIZE_X = 75;
static unsigned int TILE_SIZE_Y = 75;
static unsigned int BOARD_OFFSET_X = 360;
static unsigned int BOARD_OFFSET_Y = 165-(TILE_SIZE_Y*2);
static const int NUMBER_OF_BUBBLES = 7;
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
	
	Score* m_score;
	
	sf::Texture* m_backgroundTexture;
	sf::Sprite* m_backgroundSprite;

	sf::Texture* m_plateTexture;
	sf::Sprite* m_plateSprite;

	sf::Texture* m_frameTexture;
	sf::Sprite* m_frameSprite;

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

	void PlayComboSound(sf::Clock* &comboClock);


};

#endif