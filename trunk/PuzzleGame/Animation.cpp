#include "Animation.h"

#pragma region Constructors

Animation::Animation()
{

}

Animation::~Animation()
{

}

#pragma endregion

#pragma region Base

void Animation::Initialize(std::string sheetPath, sf::Vector2f cellSize, sf::Vector2i startPlace, int cellCount, int cellPerRow, float fps)
{
	CreateSprite(m_sprite,sheetPath);

	//Animation info
	m_cellSize = cellSize;
	m_cellPlace = startPlace.x;
	m_startRow = startPlace.y;
	m_rowChange = 0;
	m_cellCount = cellCount;
	m_cellPerRow = cellPerRow;	

	//Next animation info
	m_nextStartRow	= 0;
	m_nextCellPlace = 0;
	m_nextCellCount = 0;

	//General animation info
	m_cellSizeCountY = (m_cellSize.y * m_startRow); 
	m_nextCellSizeCountY = 0.0f;
	m_updateRate = 1.0f / (float)fps; 
	m_currentCell = 0;
	m_timeSinceUpdate = 0.0f;
	m_sheetPath = sheetPath;

	setCurrentCell();	
}

void Animation::Update()
{	
	m_timeSinceUpdate += DeltaTime;
	//std::cout << m_timeSinceUpdate << std::endl;
	//Check if it is time to update to the next cell
	if(m_timeSinceUpdate < m_updateRate)
	{
		return;
	}
	//Reset time for latest update and change to the next cell

	
	//Check if the animation continues on the next row
	if( m_currentCell == m_cellPerRow || m_cellPlace == m_cellPerRow )
	{
		m_cellPlace = 0;
		m_rowChange++;
		m_cellSizeCountY += m_cellSize.y;
	}

	//When animation is done reset animation info and begin the next animation
	if(m_currentCell == m_cellCount)
	{
		m_currentCell = 0;
//		m_cellSizeCountY -=  m_cellSize.y * m_rowChange;
		m_rowChange = 0;
//		m_cellPlace = 0;

		m_startRow = m_nextStartRow;
		m_cellPlace = m_nextCellPlace;
		//m_cellCount = m_nextCellCount;
		m_cellSizeCountY = m_nextCellSizeCountY;
	}	
	setCurrentCell();
	m_currentCell++;
	m_cellPlace++;
	m_timeSinceUpdate = 0.0f;
}

void Animation::CleanUp()
{
	delete m_sprite;
}
#pragma endregion

#pragma region Misc

void Animation::changeAnimation( sf::Vector2i startPlace, int cellCount, sf::Vector2i nextPlace,  int nextCellCount)
{
	m_startRow = startPlace.y;
	m_cellPlace = startPlace.x;
	m_cellCount = cellCount;
	m_cellSizeCountY = (m_cellSize.y * m_startRow);
   	m_rowChange = 0;
   	m_currentCell = 0;

	m_nextStartRow = nextPlace.y;
	m_nextCellPlace = nextPlace.x;
	m_nextCellCount = nextCellCount;
	m_nextCellSizeCountY = (m_cellSize.y * m_nextStartRow);
}

#pragma endregion

#pragma region GettersSetters

sf::Sprite* Animation::getSprite()
{ 
	return m_sprite; 
}

// sf::Texture* Animation::getTexture()
// {
// 	return m_texture;
// }

float Animation::getCurrentCell()
{
	return m_currentCell;
}

void Animation::setCurrentCell(float currentCell)
{
	m_currentCell = currentCell;
}

std::string Animation::getMapKey()
{
	return m_sheetPath;
}
#pragma endregion

#pragma region Helpers

void Animation::setCurrentCell()
{
	sf::IntRect currentCell = sf::IntRect(m_cellPlace * (int)m_cellSize.x, (int)m_cellSizeCountY, (int)m_cellSize.x, (int)m_cellSize.y);

	m_sprite->setTextureRect(currentCell);
}

#pragma endregion