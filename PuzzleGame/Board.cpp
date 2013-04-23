#include "Board.h"

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
	CreateBoard();

	for (unsigned int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		m_particleEffects.push_back(new ParticleEffect);
		m_particleEffects[i]->Initialize();
	}

	soundClock = new sf::Clock();
	soundClock->restart();

	m_backgroundTexture = TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/TempArt/background.png");
	CreateSprite(m_backgroundSprite, m_backgroundTexture);
	m_plateTexture = TextureProvider::Instance()->GetTexture("Assets/GraphicalAssets/TempArt/plate.png");
	CreateSprite(m_plateSprite, m_plateTexture);
	
	m_plateSprite->setPosition((float)BOARD_OFFSET_X,(float)BOARD_OFFSET_Y);

	m_boardHalfStep = 0;
	m_player1HalfStep = 0;
	m_player2HalfStep = 0;
	m_comboPitch = 1.0f;
	m_comboVolume = 200.0f;
	m_comboSoundThreshold = 5000;
}

void Board::Update()
{
	Window->clear();
	
	Window->draw(*m_backgroundSprite);
	Window->draw(*m_plateSprite);

	DrawBoard();
	for (unsigned int i = 0; i < NUMBER_OF_PARTICLES ; i++)
	{
		if (m_particleEffects[i]->IsBusy())
		{
			m_particleEffects[i]->Update();
		}
	}

	Window->display();
}

void Board::Cleanup()
{
	for (unsigned int i = 0; i < NUMBER_OF_PARTICLES; i++)
	{
		m_particleEffects[i]->Cleanup();
		delete m_particleEffects[i];
	}
	m_particleEffects.clear();
	for(unsigned int i = 0; i < m_sprites.size(); i++)
	{
		delete m_sprites.at(i);
	}

	Clean(m_backgroundTexture, m_backgroundSprite);
	Clean(m_plateTexture, m_plateSprite);

	delete m_instance;
}

#pragma endregion

#pragma region Getters

std::vector<std::vector<Tile>> Board::GetBoard()
{
	return m_board;
}

Tile* Board::GetTile(int x, int y)
{
	return &m_board.at(y).at(x);
}

int Board::GetColor(int x, int y)
{
	return m_board.at(y).at(x).GetContent();
}

int Board::GetOwner(int x, int y)
{
	return m_board.at(y).at(x).GetOwner();
}

#pragma endregion

#pragma region Setters

void Board::SetColor(int x, int y, int color)
{
	m_board.at(y).at(x).SetContent(color);
}

void Board::SetOwner(int x, int y, int owner)
{
	m_board.at(y).at(x).SetOwner(owner);
}

#pragma endregion

#pragma region Publics
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
				for (int h = 0; h < temp2; h++)
				{
					if (!m_board.at(temp[h].y).at(temp[h].x).GetFalling())
					{
						notFallingCounter++;
					}
					if (m_board.at(temp[h].y).at(temp[h].x).GetOwner() == PASSIVE)
					{
						passiveCounter++;
					}
				}
				if ((notFallingCounter == temp2) && (passiveCounter == temp2))
				{
					for (int i = 0; i < temp2;i++)
					{
						m_board.at(temp[i].y).at(temp[i].x).ClearTile();
						for (unsigned int j = 0; j < NUMBER_OF_PARTICLES; j++)
						{
							if (!m_particleEffects[j]->IsBusy())
							{
								m_particleEffects[j]->StartEffect((temp[i].x*TILE_SIZE_X)+(TILE_SIZE_X/2)+BOARD_OFFSET_X-7.5f,(temp[i].y*TILE_SIZE_Y)+(TILE_SIZE_Y/2)+BOARD_OFFSET_Y-7.5f);
								break;
							}
						}
					}
					PlayComboSound(soundClock);
				}
			}
		}
	}
}
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
			GetTile(x, y)->SetContent(0);
			GetTile(x, y)->SetOwner(0);
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

	if(y - 1 >= 0)
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

bool Board::GetBoardHalfStep()
{
	if (m_boardHalfStep > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
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

void Board::SetBoardHalfStep(int halfStep)
{
	m_boardHalfStep = halfStep;
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

#pragma region Privates

void Board::InitializeSprites()
{
	for(int i = 0; i < 7; i++)
	{
		m_sprites.push_back(new sf::Sprite());
	}
	
	for (int i = 0; i < NUMBER_OF_BUBBLES; i++)
	{
		std::ostringstream	s;
		s << i+1;
		std::string i_as_string(s.str());
		SHEET_PATH_TO_BUBBLES.push_back(PATH_TO_BUBBLES+"bubble0"+i_as_string+".png");
		TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(50,50),SHEET_PATH_TO_BUBBLES[i],m_sprites.at(i));
	}
	TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(50,50),"Assets/GraphicalAssets/Bubbles/Aura.png",m_sprites.at(5));
	TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(50,50),"Assets/GraphicalAssets/Bubbles/Aura2.png",m_sprites.at(6));

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
	int color = 0;

	for(int y = 0; y < BOARD_HEIGHT; y++)
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			DrawTile(x, y);
		}
	}
}

void Board::DrawTile(int x, int y)
{
	int color = m_board.at(y).at(x).GetContent();
	int owner = m_board.at(y).at(x).GetOwner();

	if(0 < color)
	{
		bool above = false;
		bool right = false;
		bool below = false;
		bool left = false;
		int pos = 0;

		if (m_board.at(y).at(x).GetOwner() == 0 && !m_board.at(y).at(x).GetFalling())
		{
			SetBoardHalfStep(0);
		}
		else if ((m_board.at(y).at(x).GetOwner() == 10 || m_board.at(y).at(x).GetOwner() == 11) && !m_board.at(y).at(x).GetFalling())
		{
			SetPlayer1HalfStep(0);
		}
		else if ((m_board.at(y).at(x).GetOwner() == 20 || m_board.at(y).at(x).GetOwner() == 21) && !m_board.at(y).at(x).GetFalling())
		{
			SetPlayer2HalfStep(0);
		}

		for (int i = 0; i < NrOfAdjacentSameColor(x,y); i++)
		{
			if (PositionsOfAdjacentSameColor(x,y).at(i).y == y-1)
			{
				above = true;
			}
			if (PositionsOfAdjacentSameColor(x,y).at(i).x < BOARD_WIDTH)
			{
				if (PositionsOfAdjacentSameColor(x,y).at(i).x == x+1)
				{
					right = true;
				}
			}
			if (PositionsOfAdjacentSameColor(x,y).at(i).y < BOARD_HEIGHT)
			{
				if (PositionsOfAdjacentSameColor(x,y).at(i).y == y+1)
				{
					below = true;
				}
			}
			if (PositionsOfAdjacentSameColor(x,y).at(i).x == x-1)
			{
				left = true;
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
		if ((pos < 6) && NrOfAdjacentSameColor(x,y) > 0 && m_board.at(y).at(x).GetOwner() != 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i(pos*TILE_SIZE_X,TILE_SIZE_Y*0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),SHEET_PATH_TO_BUBBLES[color-1],m_sprites.at(color - 1));
		}
		else if ((pos < 12) && NrOfAdjacentSameColor(x,y) > 0 && m_board.at(y).at(x).GetOwner() != 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i((pos-6)*TILE_SIZE_X,TILE_SIZE_Y*1),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),SHEET_PATH_TO_BUBBLES[color-1],m_sprites.at(color - 1));
		}
		else if ((pos < 18) && NrOfAdjacentSameColor(x,y) > 0 && m_board.at(y).at(x).GetOwner() != 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i((pos-12)*TILE_SIZE_X,TILE_SIZE_Y*2),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),SHEET_PATH_TO_BUBBLES[color-1],m_sprites.at(color - 1));
		}
		else if (NrOfAdjacentSameColor(x,y) == 0 || m_board.at(y).at(x).GetOwner() == 0)
		{
			TextureProvider::Instance()->GetSubRect(sf::Vector2i(0,0),sf::Vector2i(TILE_SIZE_X,TILE_SIZE_Y),SHEET_PATH_TO_BUBBLES[color-1],m_sprites.at(color - 1));
		}

		if (owner == 0)
		{
			m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_boardHalfStep);
		}
		else if (owner == 10 || owner == 11)
		{
			m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player1HalfStep);
		}
		else if (owner == 20 || owner == 21)
		{
			m_sprites.at(color - 1)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player2HalfStep);
		}

		WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(color - 1));
		if (owner == 10)
		{
			m_sprites.at(5)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player1HalfStep);
			WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(5));
		}
		else if(owner == 20)
		{
			m_sprites.at(6)->setPosition(m_board.at(y).at(x).GetPositionPixels().x+BOARD_OFFSET_X, m_board.at(y).at(x).GetPositionPixels().y+BOARD_OFFSET_Y+m_player2HalfStep);
			WindowManager::Instance()->GetWindow()->draw(*m_sprites.at(6));
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

void Board::PrintBoardToConsole()
{
	//std::system("cls");
	for(int y = 0; y < BOARD_HEIGHT; y++) 
	{
		for(int x = 0; x < BOARD_WIDTH; x++)
		{
			std::cout<< std::setw (2) << m_board.at(y).at(x).GetContent() <<' ';
		}
		
		std::cout<<'\n';
	}
	std::cout << "------------------------------------------------" << std::endl;
}
void Board::PlayComboSound(sf::Clock* &comboClock)
{
	if (comboClock->getElapsedTime().asMilliseconds() <= m_comboSoundThreshold)
	{
		m_comboPitch += 0.10f;
		m_comboVolume += 75.0f;
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