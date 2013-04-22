#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>


void LoadTexture(sf::Texture* &TextureToUse, const std::string FileName);

void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom);
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom, float x, float y);
// void CreateSprite(sf::Sprite* &SpriteToUse, Animation* &AnimationToSetFrom);
// void CreateSprite(sf::Sprite* &SpriteToUse, Animation* &AnimationToSetFrom, float x, float y);

void Clean(sf::Texture* &TextureToDelete);
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete);
// void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete, Animation* &AnimationToDelete);
// void Clean(sf::Sprite* & SpriteToDelete, Animation* &AnimationToDelete);