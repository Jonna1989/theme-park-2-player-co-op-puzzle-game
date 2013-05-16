#include "Board.h"
#include "StateManager.h"

#pragma region Base
Board::Board()
{
}

Board::~Board()
{
}

Board* Board::m_instance = 0;

Board* Board::Instance()
{
	if(m_instance == 0)
	{
		m_instance = new Board();
	}

	return m_instance;
}

void Board::Initialize()
{
	InitializeSprites();
	InitializeLevels();
	CreateBoard();
	SetBoard(4);

	for (unsigned int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		m_particleEffects.push_back(new ParticleEffect);
		m_particleEffects[i]->Initialize();
	}

	soundClock = new sf::Clock();
	soundClock->restart();

	CreateSprite(m_backgroundSprite, "Assets/GraphicalAssets/Backgrounds/background.png");
	CreateSprite(m_plateSprite, "Assets/GraphicalAssets/Backgrounds/plate.png");
	CreateSprite(m_frameSprite, "Assets/GraphicalAssets/Backgrounds/frame.png");

	//m_plateSprite->setPosition((float)BOARD_OFFSET_X-20,(float)BOARD_OFFSET_Y-20+(TILE_SIZE_Y*2));

	m_glowAnimation = new Animation();
	m_glowAnimation->Initialize("Assets/GraphicalAssets/Bubbles/glow.png", sf::Vector2f(75,75), sf::Vector2i(0,0), 26, 6, 12);

	m_player1HalfStep = 0;
	m_player2HalfStep = 0;
	m_comboPitch = 1.0f;
	m_comboVolume = 200.0f;
	m_comboSoundThreshold = 5000;
	m_score = new Score;
	m_score->Initialize(400,75,10,1,20);
}

void Board::Update()
{
	Window->draw(*m_backgroundSprite);
	Window->draw(*m_plateSprite);
	m_glowAnimation->Update();
	DrawBoard();
	Window->draw(*m_frameSprite);

	for (unsigned int i = 0; i < NUMBER_OF_PARTICLES ; i++)
	{
		if (m_particleEffects[i]->IsBusy())
		{
			m_particleEffects[i]->Update();
		}
	}
	if (soundClock->getElapsedTime().asMilliseconds() >= m_comboSoundThreshold)
	{
		m_score->SetComboMultiplier(1);
	}

	m_score->Update();
}

void Board::Cleanup()
{
	for (unsigned int i = 0; i < m_particleEffects.size(); i++)
	{
		m_particleEffects[i]->Cleanup();
		delete m_particleEffects[i];
	}
	m_particleEffects.clear();
	for(unsigned int i = 0; i < m_sprites.size(); i++)
	{
		delete m_sprites[i];
	}
	m_sprites.clear();
	delete m_glowAnimation;
	Clean(m_backgroundSprite);
	Clean(m_plateSprite);
	Clean(m_frameSprite);
	m_score->Cleanup();
	delete m_score;
}
void Board::DeleteBoardInstance()
{
	delete m_instance;
}
void Board::SetBoard(int level)
{
	int counter = 0;

	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			m_board.at(y).at(x).SetContent(m_levels.at(level - 1).at(counter));
			counter++;
		}
	}
}

#pragma endregion

#pragma region Getters

std::vector<std::vector<Tile>> Board::GetBoard()
{
	return m_board;
}

std::vector<std::string> Board::GetBubblesSheetpaths()
{
	return bubblesSheetpaths;
}

std::vector<sf::Sprite*> Board::GetSprites()
{
	return m_sprites;
}

Tile* Board::GetTile(int x, int y)
{
	return &m_board.at(y).at(x);
}

Tile* Board::GetSpecifiedTile(int owner)
{
	for (int y = 0; y < BOARD_HEIGHT ; y++)
	{
		for (int x = 0; x < BOARD_WIDTH ; x++)
		{
			if (GetTile(x,y)->GetOwner() == owner)
			{
				return GetTile(x,y);
			}
		}
	}
	return nullptr;
}

int Board::GetColor(int x, int y)
{
	return m_board.at(y).at(x).GetContent();
}

int Board::GetOwner(int x, int y)
{
	return m_board.at(y).at(x).GetOwner();
}

int Board::GetPreviousOwner(int x, int y)
{
	return m_board.at(y).at(x).GetPreviousOwner();
}

bool Board::GetPlayer1HalfStep()
{
	if (m_player1HalfStep > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::GetPlayer2HalfStep()
{
	if (m_player2HalfStep > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#pragma endregion

#pragma region Setters

void Board::SetColor(int x, int y, int color)
{
	m_board.at(y).at(x).SetContent(color);
}

void Board::SetOwner(int x, int y, int owner)
{
	SetPreviousOwner(x, y, m_board.at(y).at(x).GetOwner());
	m_board.at(y).at(x).SetOwner(owner);
}

void Board::SetPreviousOwner(int x, int y, int previousOwner) //Automatically called in Board::SetOwner
{
	if(previousOwner == 11)
	{
		previousOwner = 10;
	}
	
	if(previousOwner == 21)
	{
		previousOwner = 20;
	}

	m_board.at(y).at(x).SetPreviousOwner(previousOwner);
}

void Board::SetBoardHalfStep(int halfStep)
{
	for (int y = 2; y < BOARD_HEIGHT ; y++)
	{
		for (int x = 0; x < BOARD_WIDTH ; x++)
		{
			GetTile(x,y)->SetHalfStep(halfStep);
		}
	}
}

void Board::CheckForGameOver()
{
	bool first = false;
	bool second = false;
	bool third = false;
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		if (first && second && third)
		{
			break;
		}
		first = false;
		second = false;
		third = false;
		for (int y = 0; y < 3 ; y++)
		{
			if (GetTile(x,y)->GetContent() != 0)
			{
				if (!first)
				{
					first = true;
				}
				else if (!second)
				{
					second = true;
				}
				else if (!third)
				{
					third = true;
				}
				if (first && second && third && GetTile(x,2)->GetOwner() == 0)
				{
					Music::Instance()->Cleanup();
					Soundeffects::Instance()->PlaySound(Soundeffects::DEATHSOUND,0,1,100);
					sf::Clock tempclock;
					while (tempclock.getElapsedTime().asMilliseconds() < 2000)
					{
					}
					StateManager::Instance()->SetState(StateManager::GameLost);
					break;
				}
			}
		}
	}
}

void Board::SetPlayer1HalfStep(int halfStep)
{
	m_player1HalfStep = halfStep;
}

void Board::SetPlayer2HalfStep(int halfStep)
{
	m_player2HalfStep = halfStep;
}

#pragma endregion

#pragma region Publics

bool Board::IsTileVacant(int x, int y)
{
	if((0 <= x && x < BOARD_WIDTH) && (0 <= y && y < BOARD_HEIGHT))
	{
		if(GetTile(x, y)->GetContent() == EMPTY_SPACE)
		{
			return true;
		}
	}
	return false;
}

void Board::DropTile(int x, int y)
{
	if(y < BOARD_HEIGHT - 1)
	{
		if(IsTileVacant(x, y + 1) && GetTile(x,y)->GetOwner() == 0)
		{
			GetTile(x, y + 1)->SetContent(GetTile(x, y)->GetContent());
			GetTile(x, y + 1)->SetOwner(GetTile(x, y)->GetOwner());
			GetTile(x, y + 1)->SetMarker(GetTile(x, y)->GetMarker());
			GetTile(x, y)->SetContent(0);
			GetTile(x, y)->SetOwner(0);
			GetTile(x, y)->SetMarker(0);
		}
	}
}

int Board::NrOfAdjacentSameColor(int x, int y)
{
	return PositionsOfAdjacentSameColor(x, y).size();
}

std::vector<sf::Vector2i> Board::PositionsOfAdjacentSameColor(int x, int y)
{
	std::vector<sf::Vector2i> sameColorPositions;

	if(y - 1 >= 2)
	{
		if(m_board.at(y - 1).at(x).GetContent() == m_board.at(y).at(x).GetContent())
		{
			sameColorPositions.push_back(m_board.at(y - 1).at(x).GetPositionVector());
		}
	}

	if(x + 1 < BOARD_WIDTH)
	{
		if(m_board.at(y).at(x + 1).GetContent() == m_board.at(y).at(x).GetContent())
		{
			sameColorPositions.push_back(m_board.at(y).at(x + 1).GetPositionVector());
		}
	}

	if(y + 1 < BOARD_HEIGHT)
	{
		if(m_board.at(y + 1).at(x).GetContent() == m_board.at(y).at(x).GetContent())
		{
			sameColorPositions.push_back(m_board.at(y + 1).at(x).GetPositionVector());
		}
	}

	if(x - 1 >= 0)
	{
		if(m_board.at(y).at(x - 1).GetContent() == m_board.at(y).at(x).GetContent())
		{
			sameColorPositions.push_back(m_board.at(y).at(x - 1).GetPositionVector());
		}
	}
	if (m_board.at(y).at(x).GetContent() == 0)
	{
		sameColorPositions.clear();
	}
	return sameColorPositions;
}

int Board::NrOfConnectedSameColor(int x, int y)
{
	return PositionsOfConnectedSameColor(x, y).size();
}

std::vector<sf::Vector2i> Board::PositionsOfConnectedSameColor(int x, int y)
{
	std::vector<sf::Vector2i> positions = PositionsOfAdjacentSameColor(x, y);
	std::vector<sf::Vector2i> additionalPositions;
	bool identical = false;

	for(unsigned int i = 0; i < positions.size(); i++)
	{
		additionalPositions.clear();
		additionalPositions = PositionsOfAdjacentSameColor(positions.at(i).x, positions.at(i).y);

		if(additionalPositions.size() > 1)
		{
			for(unsigned int j = 0; j < additionalPositions.size(); j++)
			{
				identical = false; 

				for(unsigned int k = 0; k < positions.size(); k++)
				{
					if(additionalPositions.at(j) == positions.at(k))
					{
						identical = true;
						break;
					}
				}

				if(!identical)
				{
					positions.push_back(additionalPositions.at(j));
				}
			}
		}
	}	

	return positions;
}

void Board::CheckForMatch()
{
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			CheckForFall(x,y);
			if (NrOfConnectedSameColor(x,y) > 3)
			{
				int temp2 = NrOfConnectedSameColor(x,y);
				std::vector<sf::Vector2i> temp = PositionsOfConnectedSameColor(x,y);
				int notFallingCounter = 0;
				int passiveCounter = 0;
				int previousOwnerP1 = 0;
				int previousOwnerP2 = 0;
				int markerP1 = 0;
				int markerP2 = 0;
				float avragePosX = 0;
				float avragePosY = 0;
				for (int h = 0; h < temp2; h++)
				{
					avragePosX += (((m_board.at(temp[h].y).at(temp[h].x).GetPositionVector().x)*TILE_SIZE_X)+BOARD_OFFSET_X+TILE_SIZE_X/4);
					avragePosY += (((m_board.at(temp[h].y).at(temp[h].x).GetPositionVector().y)*TILE_SIZE_Y)+BOARD_OFFSET_Y);
					if (!m_board.at(temp[h].y).at(temp[h].x).GetFalling())
					{
						notFallingCounter++;
					}
					if (m_board.at(temp[h].y).at(temp[h].x).GetOwner() == PASSIVE)
					{
						passiveCounter++;
					}
					if ((m_board.at(temp[h].y).at(temp[h].x).GetPreviousOwner() == 10)
						||(m_board.at(temp[h].y).at(temp[h].x).GetPreviousOwner() == 11))
					{
						previousOwnerP1++;
					}
					if ((m_board.at(temp[h].y).at(temp[h].x).GetPreviousOwner() == 20)
						||(m_board.at(temp[h].y).at(temp[h].x).GetPreviousOwner() == 21))
					{
						previousOwnerP2++;
					}
					if ((m_board.at(temp[h].y).at(temp[h].x).GetMarker() == 1))
					{
						markerP1++;
					}
					if ((m_board.at(temp[h].y).at(temp[h].x).GetMarker() == 2))
					{
						markerP2++;
					}
				}
				if ((notFallingCounter == temp2) && (passiveCounter == temp2))
				{
				int particleColor = 0;
				particleColor = GetTile(x,y)->GetContent();
					for (int i = 0; i < temp2;i++)
					{
						m_board.at(temp[i].y).at(temp[i].x).ClearTile();
						for (unsigned int j = 0; j < NUMBER_OF_PARTICLES; j++)
						{
							if (!m_particleEffects[j]->IsBusy())
							{
								int tempBonus = 1;
								if (markerP1 > 0 && markerP2 > 0)
								{
									tempBonus = 2;
								}
								m_particleEffects[j]->StartEffect((temp[i].x*TILE_SIZE_X)+(TILE_SIZE_X/2)+BOARD_OFFSET_X-7.5f,(temp[i].y*TILE_SIZE_Y)+(TILE_SIZE_Y/2)+BOARD_OFFSET_Y-7.5f, particleColor, tempBonus);
								break;
							}
						}
					}
					PlayComboSound(soundClock);
					avragePosX /= temp2; 
					avragePosY /= temp2;
					m_score->AddScore(temp2, avragePosX, avragePosY, markerP1, markerP2);
					m_score->ResetScoreMultiplier();
				}
			}
		}
	}
}

void Board::CheckForFall(int x, int y)
{
	if (y < BOARD_HEIGHT-1)
	{
		if (m_board.at(y+1).at(x).GetContent() == EMPTY_SPACE
			|| m_board.at(y+1).at(x).GetOwner() != PASSIVE)
		{
			if (m_board.at(y+1).at(x).GetOwner() != 0)
			{
				if (m_board.at(y+1).at(x).GetFalling() || (m_board.at(y+1).at(x).GetContent() == EMPTY_SPACE))
				{
					m_board.at(y).at(x).SetFalling(true);
				}
				else
				{
					m_board.at(y).at(x).SetFalling(false);
				}
			}
			else
			{
				m_board.at(y).at(x).SetFalling(true);
			}
		}
		else
		{
			if (m_board.at(y+1).at(x).GetContent() != EMPTY_SPACE)
			{
				m_board.at(y).at(x).SetFalling(false);
			}
		}
	}
	else
	{
		m_board.at(y).at(x).SetFalling(false);
	}
}

void Board::DrawNextPiece(sf::Vector2f positionOne, sf::Vector2f positionTwo, int colorOne, int colorTwo)
{
	m_sprites.at(colorOne - 1)->setPosition(positionOne);
	TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[colorOne-1],m_sprites.at(colorOne - 1));
	WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(colorOne - 1));
	m_sprites.at(colorTwo - 1)->setPosition(positionTwo);
	TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[colorTwo-1],m_sprites.at(colorTwo - 1));
	WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(colorTwo - 1));
}

void Board::PrintBoardToConsole()
{
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			std::cout<< std::setw (2) << m_board.at(y).at(x).GetContent() <<' ';
		}
		
		std::cout<<'\n';
	}
	std::cout << "------------------------------------------------" << std::endl;
}

#pragma endregion

#pragma region Privates

void Board::InitializeSprites()
{
	for(int i = 0; i < NUMBER_OF_BUBBLES + 6; i++)
	{
		m_sprites.push_back(new sf::Sprite());
	}
	
	for (int i = 0; i < NUMBER_OF_BUBBLES; i++)
	{
		bubblesSheetpaths.push_back(PATH_TO_BUBBLES+"bubble0"+ConvertIntToStdString(i+1)+".png");
		TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[i],m_sprites.at(i));
	}
	m_sprites[NUMBER_OF_BUBBLES]->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Bubbles/Aura.png"));
	m_sprites[NUMBER_OF_BUBBLES+1]->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Bubbles/Aura2.png"));
	m_sprites[NUMBER_OF_BUBBLES+2]->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Bubbles/AuraTransparent.png"));
	m_sprites[NUMBER_OF_BUBBLES+3]->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/Bubbles/Aura2Transparent.png"));
	m_sprites[NUMBER_OF_BUBBLES+4]->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/TempArt/Bomb.png"));
	m_sprites[NUMBER_OF_BUBBLES+5]->setTexture(*TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/TempArt/Colorbomb.png"));		
}

void Board::InitializeLevels()
{
	ReadTextLevels(PATH_LEVEL_1);	
	ReadTextLevels(PATH_LEVEL_2);
	ReadTextLevels(PATH_LEVEL_3);
	ReadTextLevels(PATH_LEVEL_4);
}

void Board::ReadTextLevels(std::string sheetPath)
{
	int color = 0;
	std::string nextChar;
	std::string currentChar;
	std::ifstream iStream(sheetPath);
	std::vector<int> levelColors;

	while(iStream.good())
	{
		nextChar = iStream.peek();

		if(nextChar != " " && nextChar != "\n")
		{
			currentChar = iStream.get();
			color = atoi(currentChar.c_str());
			levelColors.push_back(color);
		}
		else
		{
			iStream.ignore();
		}
	}

	levelColors.pop_back();

	if (levelColors.size() == BOARD_HEIGHT * BOARD_WIDTH)
	{
		m_levels.push_back(levelColors);
		levelColors.clear();
	}
	else
	{
		std::cout << "Error, wrong number of colors read\n";
	}

	iStream.close();
}

void Board::CreateBoard()
{
	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		m_board.push_back(std::vector<Tile>());

		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			m_board.at(y).push_back(Tile());
			m_board.at(y).at(x).Initialize(TILE_SIZE_X, TILE_SIZE_Y, x, y);
		}
	}
}

void Board::DrawBoard()
{
	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			if(x == 8 && y == 2 && GetTile(8,2)->GetContent() == 11)
			{
				DrawTile(x, y);
			}
			else
			{
				DrawTile(x, y);
			}
		}
	}
	DrawGlow();
}

#pragma region DrawTile

void Board::DrawTile(int x, int y)
{
	int color = GetTile(x, y)->GetContent();
	int owner = GetTile(x, y)->GetOwner();
	int marker = GetTile(x,y)->GetMarker();

	if(0 < color)
	{
		bool above = false;
		bool right = false;
		bool below = false;
		bool left = false;
		int pos = 0;

		CheckForFall(x,y);

		if (m_board.at(y).at(x).GetOwner() == 0 && !m_board.at(y).at(x).GetFalling())
		{
			m_board.at(y).at(x).SetHalfStep(0);
		
		}
		else if ((m_board.at(y).at(x).GetOwner() == 10 || m_board.at(y).at(x).GetOwner() == 11))
		{
			if ( y < BOARD_HEIGHT-2)
			{
				if ((m_board.at(y+1).at(x).GetContent() != EMPTY_SPACE && !m_board.at(y+1).at(x).GetFalling())
					|| (m_board.at(y+1).at(x).GetOwner() == 20
					|| m_board.at(y+1).at(x).GetOwner() == 21
					/*|| m_board.at(y+2).at(x).GetOwner() == 20
					|| m_board.at(y+2).at(x).GetOwner() == 21*/))
				{
					SetPlayer1HalfStep(0);
				}

				if (m_board.at(y).at(x).GetOwner() == 10 && GetSpecifiedTile(11) != nullptr)
				{
					if (GetSpecifiedTile(11)->GetPositionVector().y == y) // Horizontally Aligned
					{
						if (GetSpecifiedTile(11)->GetPositionVector().x == x+1 && (x+1 <= BOARD_WIDTH)) // To the right
						{
							if (GetTile(x+1, y+1)->GetOwner() != 0)
							{
								SetPlayer1HalfStep(0);
							}
						}
						else if (GetSpecifiedTile(11)->GetPositionVector().x == x-1 && (x-1 >= 0)) // To the left
						{
							if (GetTile(x-1, y+1)->GetOwner() != 0)
							{
								SetPlayer1HalfStep(0);
							}
						}
					}
					else if (GetSpecifiedTile(11)->GetPositionVector().y == y+1) // Below
					{
						if (GetTile(x, y+2)->GetOwner() != 0)
						{
							SetPlayer1HalfStep(0);
						}
					}
				}
				else if (m_board.at(y).at(x).GetOwner() == 11 && GetSpecifiedTile(10) != nullptr)
				{
					if (GetSpecifiedTile(10)->GetPositionVector().y == y) // Horizontally Aligned
					{
						if (GetSpecifiedTile(10)->GetPositionVector().x == x+1 && (x+1 >= BOARD_WIDTH)) // To the right
						{
							if (GetTile(x+1, y+1)->GetOwner() != 0)
							{
								SetPlayer1HalfStep(0);
							}
						}
						else if (GetSpecifiedTile(10)->GetPositionVector().x == x-1 && (x-1 >= 0)) // To the left
						{
							if (GetTile(x-1, y+1)->GetOwner() != 0)
							{
								SetPlayer1HalfStep(0);
							}
						}
					}
					else if (GetSpecifiedTile(10)->GetPositionVector().y == y+1) // Below
					{
						if (GetTile(x, y+2)->GetOwner() != 0)
						{
							SetPlayer1HalfStep(0);
						}
					}
				}
			}
			else if ( y < BOARD_HEIGHT-1)
			{
				if ((m_board.at(y+1).at(x).GetContent() != EMPTY_SPACE && !m_board.at(y+1).at(x).GetFalling())
					|| (m_board.at(y+1).at(x).GetOwner() == 20
					|| m_board.at(y+1).at(x).GetOwner() == 21))
				{
					SetPlayer1HalfStep(0);
				}
			}
			else
			{
				SetPlayer1HalfStep(0);
			}
			if (GetSpecifiedTile(10) != nullptr && GetSpecifiedTile(11) != nullptr)
			{
				if (GetSpecifiedTile(10)->GetPositionVector().y < 2 || GetSpecifiedTile(11)->GetPositionVector().y < 2)
				{
					SetPlayer1HalfStep(0);
				}
			}
		}
		else if ((m_board.at(y).at(x).GetOwner() == 20 || m_board.at(y).at(x).GetOwner() == 21))
		{
			if ( y < BOARD_HEIGHT-2)
			{
				if ((m_board.at(y+1).at(x).GetContent() != EMPTY_SPACE && !m_board.at(y+1).at(x).GetFalling())
					|| (m_board.at(y+1).at(x).GetOwner() == 10
					|| m_board.at(y+1).at(x).GetOwner() == 11
					/*|| m_board.at(y+2).at(x).GetOwner() == 10
					|| m_board.at(y+2).at(x).GetOwner() == 11*/))
				{
					SetPlayer2HalfStep(0);
				}

				if (m_board.at(y).at(x).GetOwner() == 20 && GetSpecifiedTile(21) != nullptr)
				{
					if (GetSpecifiedTile(21)->GetPositionVector().y == y) // Horizontally Aligned
					{
						if (GetSpecifiedTile(21)->GetPositionVector().x == x+1 && (x+1 <= BOARD_HEIGHT)) // To the right
						{
							if (GetTile(x+1, y+1)->GetOwner() != 0)
							{
								SetPlayer2HalfStep(0);
							}
						}
						else if (GetSpecifiedTile(21)->GetPositionVector().x == x-1 && (x-1 >= 0)) // To the left
						{
							if (GetTile(x-1,y+1)->GetOwner() != 0)
							{
								SetPlayer2HalfStep(0);
							}
						}
					}
					else if (GetSpecifiedTile(21)->GetPositionVector().y == y+1) // Below
					{
						if (GetTile(x,y+2)->GetOwner() != 0)
						{
							SetPlayer2HalfStep(0);
						}
					}
				}
				else if (m_board.at(y).at(x).GetOwner() == 21 && GetSpecifiedTile(20) != nullptr)
				{
					if (GetSpecifiedTile(20)->GetPositionVector().y == y) // Horizontally Aligned
					{
						if (GetSpecifiedTile(20)->GetPositionVector().x == x+1 && (x+1 <= BOARD_HEIGHT)) // To the right
						{
							if (GetTile(x+1, y+1)->GetOwner() != 0)
							{
								SetPlayer2HalfStep(0);
							}
						}
						else if (GetSpecifiedTile(20)->GetPositionVector().x == x-1 && (x-1 >= 0)) // To the left
						{
							if (GetTile(x-1,y+1)->GetOwner() != 0)
							{
								SetPlayer2HalfStep(0);
							}
						}
					}
					else if (GetSpecifiedTile(20)->GetPositionVector().y == y+1) // Below
					{
						if (GetTile(x,y+2)->GetOwner() != 0)
						{
							SetPlayer2HalfStep(0);
						}
					}
				}
			}
			else if ( y < BOARD_HEIGHT-1)
			{
				if ((m_board.at(y+1).at(x).GetContent() != EMPTY_SPACE && !m_board.at(y+1).at(x).GetFalling())
					|| (m_board.at(y+1).at(x).GetOwner() == 10
					|| m_board.at(y+1).at(x).GetOwner() == 11))
				{
					SetPlayer2HalfStep(0);
				}
			}
			else
			{
				SetPlayer2HalfStep(0);
			}
			if (GetSpecifiedTile(20) != nullptr && GetSpecifiedTile(21) != nullptr)
			{
				if (GetSpecifiedTile(20)->GetPositionVector().y < 2 || GetSpecifiedTile(21)->GetPositionVector().y < 2)
				{
					SetPlayer2HalfStep(0);
				}
			}
		}

		for (int i = 0; i < NrOfAdjacentSameColor(x,y); i++)
		{
			if (PositionsOfAdjacentSameColor(x,y).at(i).y == y-1)
			{
				if (GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetOwner() == 0
					&& !GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetFalling()
					&& !GetTile(x,y)->GetFalling())
				{
					above = true;
				}
			}
			if (PositionsOfAdjacentSameColor(x,y).at(i).x < BOARD_WIDTH)
			{
				if (PositionsOfAdjacentSameColor(x,y).at(i).x == x+1)
				{
					if (GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetOwner() == 0
						&& !GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetFalling()
						&& !GetTile(x,y)->GetFalling())
					{
						right = true;
					}
				}
			}
			if (PositionsOfAdjacentSameColor(x,y).at(i).y < BOARD_HEIGHT)
			{
				if (PositionsOfAdjacentSameColor(x,y).at(i).y == y+1)
				{
					if (GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetOwner() == 0
						&& !GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetFalling()
						&& !GetTile(x,y)->GetFalling())
					{
						below = true;
					}
				}
			}
			if (PositionsOfAdjacentSameColor(x,y).at(i).x == x-1)
			{
				if (GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetOwner() == 0
					&& !GetTile(PositionsOfAdjacentSameColor(x,y).at(i).x,PositionsOfAdjacentSameColor(x,y).at(i).y)->GetFalling()
					&& !GetTile(x,y)->GetFalling())
				{
					left = true;
				}
			}
		}
#pragma region BubbleChecking

		if (!above && !right && !below && !left) // Normal Bubble
		{
			pos = 0;
		}
		else if (!above && right && !below && !left) // Right-Connected Bubble
		{
			pos = 1;
		}
		else if (!above && !right && !below && left) // Left-Connected Bubble
		{
			pos = 2;
		}
		else if (!above && !right && below && !left) // Down-Connected Bubble
		{
			pos = 3;
		}
		else if (above && !right && !below && !left) // Up-Connected Bubble
		{
			pos = 4;
		}
		else if (!above && right && !below && left) // Right/Left-Connected Bubble
		{
			pos = 5;
		}
		else if (!above && right && below && left) // Right/Left/Down-Connected Bubble
		{
			pos = 6;
		}
		else if (above && right && below && left) // Right/Left/Down/Up-Connected Bubble
		{
			pos = 7;
		}
		else if (above && right && !below && left) // Right/Left/Up-Connected Bubble
		{
			pos = 8;
		}
		else if (above && right && below && !left) // Right/Down/Up-Connected Bubble
		{
			pos = 9;
		}
		else if (above && right && !below && !left) // Right/Up-Connected Bubble
		{
			pos = 10;
		}
		else if (!above && right && below && !left) // Right/Down-Connected Bubble
		{
			pos = 11;
		}
		else if (above && !right && below && left) // Left/Down/Up-Connected Bubble
		{
			pos = 12;
		}
		else if (!above && !right && below && left) // Left/Down-Connected Bubble
		{
			pos = 13;
		}
		else if (above && !right && !below && left) // Left/Up-Connected Bubble
		{
			pos = 14;
		}
		else if (above && !right && below && !left) // Down/Up-Connected Bubble
		{
			pos = 15;
		}

#pragma endregion

		if ((pos < 6) && NrOfAdjacentSameColor(x,y) > 0 && m_board.at(y).at(x).GetOwner() == 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i(pos*TILE_SIZE_X,TILE_SIZE_Y*0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[color-1],m_sprites.at(color - 1));
		}
		else if ((pos < 12) && NrOfAdjacentSameColor(x,y) > 0 && m_board.at(y).at(x).GetOwner() == 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i((pos-6)*TILE_SIZE_X,TILE_SIZE_Y*1),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[color-1],m_sprites.at(color - 1));
		}
		else if ((pos < 18) && NrOfAdjacentSameColor(x,y) > 0 && m_board.at(y).at(x).GetOwner() == 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i((pos-12)*TILE_SIZE_X,TILE_SIZE_Y*2),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[color-1],m_sprites.at(color - 1));
		}
		else if (NrOfAdjacentSameColor(x,y) == 0 && GetTile(x, y)->GetOwner() == 0 && GetTile(x, y)->GetContent() > 10)
		{
			
		}
		else if (NrOfAdjacentSameColor(x,y) == 0 || GetTile(x, y)->GetOwner() != 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),bubblesSheetpaths[color-1],m_sprites.at(color - 1));
		}

		if (owner == PASSIVE)
		{
			if(color <= 10)
			{
				m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_board.at(y).at(x).GetHalfStep());
			}
			else
			{
				m_sprites.at(color)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_board.at(y).at(x).GetHalfStep());
			}
		}
		else if (owner == 10 || owner == 11)
		{
			m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player1HalfStep);
		}
		else if (owner == 20 || owner == 21)
		{
			m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player2HalfStep);
		}
		if (y >= 2)
		{
			WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(color - 1));
			if (owner == 10)
			{
				m_sprites.at(NUMBER_OF_BUBBLES)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player1HalfStep);
				WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(NUMBER_OF_BUBBLES));
			}
			else if(owner == 20)
			{
				m_sprites.at(NUMBER_OF_BUBBLES+1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player2HalfStep);
				WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(NUMBER_OF_BUBBLES+1));
			}

			if (marker == 1 && !GetTile(x,y)->GetFalling())
			{
				m_sprites.at(NUMBER_OF_BUBBLES+2)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y);
				WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(NUMBER_OF_BUBBLES+2));
			}
			else if (marker == 2 && !GetTile(x,y)->GetFalling())
			{
				m_sprites.at(NUMBER_OF_BUBBLES+3)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y);
				WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(NUMBER_OF_BUBBLES+3));
			}

			if (GetColor(x, y) == 11 && !GetTile(x,y)->GetFalling())
			{
				m_sprites.at(NUMBER_OF_BUBBLES+4)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y);
				WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(NUMBER_OF_BUBBLES+4));			
			}

			if (GetColor(x, y) == 12 && !GetTile(x,y)->GetFalling())
			{
				m_sprites.at(NUMBER_OF_BUBBLES+5)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y);
				WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(NUMBER_OF_BUBBLES+5));			
			}
		}
	}
}

void Board::DrawGlow()
{
	bool preventDraw = false;
	for (int y = 0; y < BOARD_HEIGHT ; y++)
	{
		for (int x = 0; x < BOARD_WIDTH ; x++)
		{
			if (!GetTile(x,y)->GetFalling())
			{
				if (GetSpecifiedTile(10) != nullptr && GetSpecifiedTile(11) != nullptr)
				{
					if ((GetSpecifiedTile(10)->GetContent() == GetTile(x,y)->GetContent()) || (GetSpecifiedTile(11)->GetContent() == GetTile(x,y)->GetContent())
						&& GetTile(x,y)->GetOwner() == 0)
					{
						if (NrOfAdjacentSameColor(x,y) == 2
							&& !(PositionsOfConnectedSameColor(x,y)[0].x == x && PositionsOfConnectedSameColor(x,y)[0].y == y
							&& GetTile(PositionsOfConnectedSameColor(x,y)[0].x,PositionsOfConnectedSameColor(x,y)[0].y)->GetOwner() == 0)
							&& !(PositionsOfConnectedSameColor(x,y)[1].x == x && PositionsOfConnectedSameColor(x,y)[1].y == y
							&& GetTile(PositionsOfConnectedSameColor(x,y)[1].x,PositionsOfConnectedSameColor(x,y)[1].y)->GetOwner() == 0))
						{
							for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
							{
								if (PositionsOfConnectedSameColor(x,y)[i].x > 1
									&& PositionsOfConnectedSameColor(x,y)[i].x < BOARD_WIDTH-2
									&& PositionsOfConnectedSameColor(x,y)[i].y > 2)
								{
									preventDraw = true;
									if (GetTile(PositionsOfConnectedSameColor(x,y)[i].x-1,PositionsOfConnectedSameColor(x,y)[i].y)->GetContent() == 0
										|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x+1,PositionsOfConnectedSameColor(x,y)[i].y)->GetContent() == 0
										|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y-1)->GetContent() == 0)
									{
										preventDraw = false;
										break;
									}
								}
								else
								{
									preventDraw = true;
								}
							}
							for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
							{
								if (GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y)->GetFalling()
									|| GetTile(x,y)->GetFalling()
									|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y)->GetOwner() != 0)
								{
									preventDraw = true;
								}
							}
							if (!preventDraw)
							{
								m_glowAnimation->getSprite()->setPosition(x*(float)TILE_SIZE_X+(float)BOARD_OFFSET_X,y*(float)TILE_SIZE_Y+(float)BOARD_OFFSET_Y);
								Window->draw(*m_glowAnimation->getSprite());
								for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
								{
									m_glowAnimation->getSprite()->setPosition(PositionsOfConnectedSameColor(x,y)[i].x*(float)TILE_SIZE_X+(float)BOARD_OFFSET_X,PositionsOfConnectedSameColor(x,y)[i].y*(float)TILE_SIZE_Y+(float)BOARD_OFFSET_Y);
									Window->draw(*m_glowAnimation->getSprite());
								}
							}
						}
					}
					else if (GetSpecifiedTile(20) != nullptr && GetSpecifiedTile(21) != nullptr)
					{
						if ((GetSpecifiedTile(20)->GetContent() == GetTile(x,y)->GetContent()) || (GetSpecifiedTile(21)->GetContent() == GetTile(x,y)->GetContent())
							&& GetTile(x,y)->GetOwner() == 0)
						{
							if (NrOfAdjacentSameColor(x,y) == 2
								&& !(PositionsOfConnectedSameColor(x,y)[0].x == x && PositionsOfConnectedSameColor(x,y)[0].y == y
								&& GetTile(PositionsOfConnectedSameColor(x,y)[0].x,PositionsOfConnectedSameColor(x,y)[0].y)->GetOwner() == 0)
								&& !(PositionsOfConnectedSameColor(x,y)[1].x == x && PositionsOfConnectedSameColor(x,y)[1].y == y
								&& GetTile(PositionsOfConnectedSameColor(x,y)[1].x,PositionsOfConnectedSameColor(x,y)[1].y)->GetOwner() == 0))
							{
								for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
								{
									if (PositionsOfConnectedSameColor(x,y)[i].x > 1
										&& PositionsOfConnectedSameColor(x,y)[i].x < BOARD_WIDTH-2
										&& PositionsOfConnectedSameColor(x,y)[i].y > 2)
									{
										preventDraw = true;
										if (GetTile(PositionsOfConnectedSameColor(x,y)[i].x-1,PositionsOfConnectedSameColor(x,y)[i].y)->GetContent() == 0
											|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x+1,PositionsOfConnectedSameColor(x,y)[i].y)->GetContent() == 0
											|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y-1)->GetContent() == 0)
										{
											preventDraw = false;
											break;
										}
									}
									else
									{
										preventDraw = true;
									}
								}
								for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
								{
									if (GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y)->GetFalling()
										|| GetTile(x,y)->GetFalling()
										|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y)->GetOwner() != 0)
									{
										preventDraw = true;
									}
								}
								if (!preventDraw)
								{
									m_glowAnimation->getSprite()->setPosition(x*(float)TILE_SIZE_X+(float)BOARD_OFFSET_X,y*(float)TILE_SIZE_Y+(float)BOARD_OFFSET_Y);
									Window->draw(*m_glowAnimation->getSprite());
									for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
									{
										m_glowAnimation->getSprite()->setPosition(PositionsOfConnectedSameColor(x,y)[i].x*(float)TILE_SIZE_X+(float)BOARD_OFFSET_X,PositionsOfConnectedSameColor(x,y)[i].y*(float)TILE_SIZE_Y+(float)BOARD_OFFSET_Y);
										Window->draw(*m_glowAnimation->getSprite());
									}
								}
							}
						}
					}
				}
				else if (GetSpecifiedTile(20) != nullptr && GetSpecifiedTile(21) != nullptr)
				{
					if ((GetSpecifiedTile(20)->GetContent() == GetTile(x,y)->GetContent()) || (GetSpecifiedTile(21)->GetContent() == GetTile(x,y)->GetContent())
						&& GetTile(x,y)->GetOwner() == 0)
					{
						if (NrOfAdjacentSameColor(x,y) == 2
							&& !(PositionsOfConnectedSameColor(x,y)[0].x == x && PositionsOfConnectedSameColor(x,y)[0].y == y
							&& GetTile(PositionsOfConnectedSameColor(x,y)[0].x,PositionsOfConnectedSameColor(x,y)[0].y)->GetOwner() == 0)
							&& !(PositionsOfConnectedSameColor(x,y)[1].x == x && PositionsOfConnectedSameColor(x,y)[1].y == y
							&& GetTile(PositionsOfConnectedSameColor(x,y)[1].x,PositionsOfConnectedSameColor(x,y)[1].y)->GetOwner() == 0))
						{
							for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
							{
								if (PositionsOfConnectedSameColor(x,y)[i].x > 1
									&& PositionsOfConnectedSameColor(x,y)[i].x < BOARD_WIDTH-2
									&& PositionsOfConnectedSameColor(x,y)[i].y > 2)
								{
									preventDraw = true;
									if (GetTile(PositionsOfConnectedSameColor(x,y)[i].x-1,PositionsOfConnectedSameColor(x,y)[i].y)->GetContent() == 0
										|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x+1,PositionsOfConnectedSameColor(x,y)[i].y)->GetContent() == 0
										|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y-1)->GetContent() == 0)
									{
										preventDraw = false;
										break;
									}
								}
								else
								{
									preventDraw = true;
								}
							}
							for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
							{
								if (GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y)->GetFalling()
									|| GetTile(x,y)->GetFalling()
									|| GetTile(PositionsOfConnectedSameColor(x,y)[i].x,PositionsOfConnectedSameColor(x,y)[i].y)->GetOwner() != 0)
								{
									preventDraw = true;
								}
							}
							if (!preventDraw)
							{
								m_glowAnimation->getSprite()->setPosition(x*(float)TILE_SIZE_X+(float)BOARD_OFFSET_X,y*(float)TILE_SIZE_Y+(float)BOARD_OFFSET_Y);
								Window->draw(*m_glowAnimation->getSprite());
								for (unsigned int i = 0; i < PositionsOfConnectedSameColor(x,y).size(); i++)
								{
									m_glowAnimation->getSprite()->setPosition(PositionsOfConnectedSameColor(x,y)[i].x*(float)TILE_SIZE_X+(float)BOARD_OFFSET_X,PositionsOfConnectedSameColor(x,y)[i].y*(float)TILE_SIZE_Y+BOARD_OFFSET_Y);
									Window->draw(*m_glowAnimation->getSprite());
								}
							}
						}
					}
				}
			}
		}
	}
}

#pragma endregion

void Board::PlayComboSound(sf::Clock* &comboClock)
{
	if (comboClock->getElapsedTime().asMilliseconds() <= m_comboSoundThreshold)
	{
		m_comboPitch += 0.10f;
		m_comboVolume += 75.0f;
		m_score->IncreaseComboMultiplier(1);
		Soundeffects::Instance()->PlaySound(Soundeffects::POPSOUND,0,m_comboPitch,m_comboVolume);
	}
	else
	{
		m_comboPitch = 1.0f;
		m_comboVolume = 200.0f;
		Soundeffects::Instance()->PlaySound(Soundeffects::POPSOUND,0,m_comboPitch,m_comboVolume);
	}
	comboClock->restart();
}

#pragma endregion