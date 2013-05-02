#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

void LoadTexture(sf::Texture* &TextureToUse, const std::string FileName);

void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom);
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom, float x, float y);

void Clean(sf::Texture* &TextureToDelete);
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete);

void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition);
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY);
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor);
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor);

void ConvertIntToSfString(int intToGetStringFrom,sf::String &sfStringToUpdateFrom);
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo);
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd);