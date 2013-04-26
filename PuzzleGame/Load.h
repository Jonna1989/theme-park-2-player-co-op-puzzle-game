#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>


void LoadTexture(sf::Texture* &TextureToUse, const std::string FileName);

void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom);
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom, float x, float y);

void Clean(sf::Texture* &TextureToDelete);
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete);

void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition);
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY);
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor);
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor);
