#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TextureProvider.h"
#include <cmath>
void LoadTexture(sf::Texture* &TextureToUse, const std::string &FileName);

void CreateSprite(sf::Sprite* &SpriteToUse);
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom);
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom, float x, float y);
void CreateSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture);
void CreateSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture, float x, float y);

void SetSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture);
void SetSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture, float x, float y);

void Clean(sf::Texture* &TextureToDelete);
void Clean(sf::Sprite* &SpriteToDelete);
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete);

void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition);
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY);
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor);
void DeclareSfText(sf::Text* &textToDeclare, sf::Font* font, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY);
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor);
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, sf::Font* font, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor);


void ConvertIntToSfString(int intToGetStringFrom,sf::String &sfStringToUpdateFrom);
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo);
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd);

std::string ConvertIntToStdString(int intToConvert);
std::string ConvertCharToStdString(char charToConvert);
int RandomNumber();
int RandomNumber(int lowRange, int highRange);
char ConvertIntToChar(int intToConvert);

unsigned GetNumberOfDigits (unsigned i);