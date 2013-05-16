#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "TextureProvider.h"
#include "FrameTime.h"


class Animation
{
public:
	//Constructors
	Animation();
	~Animation();

	//Base
	void Initialize(std::string sheetPath, sf::Vector2f cellSize, sf::Vector2i startPlace, int cellCount, int cellPerRow, float fps);
	void Update();
	void CleanUp();

	//Misc functions
	void changeAnimation(sf::Vector2i startPlace, int cellCount, sf::Vector2i nextPlace, int nextCellCount);

	//Getters & Setters
	sf::Sprite* getSprite();
	float getCurrentCell();

	std::string getMapKey();

	void setCurrentCell(float currentCell);

	float m_updateRate;

private:
	sf::Sprite* m_sprite;

	std::string m_sheetPath;

	sf::Vector2f m_cellSize;
	int m_cellCount;
	int m_startRow;
	int m_rowChange;
	int m_cellPlace;
	int m_cellPerRow;

	int m_nextStartRow;
	int m_nextCellPlace;
	int m_nextCellCount;
	
	float m_cellSizeCountY;
	float m_nextCellSizeCountY;
	
	float m_currentCell;
	float m_timeSinceUpdate;	

	//Helper functions
	void setCurrentCell();
};

#endif