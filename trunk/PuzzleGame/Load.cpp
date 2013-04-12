#include "Load.h"

void LoadTexture(sf::Texture* &TextureToUse, const std::string FileName)
{
	TextureToUse = new sf::Texture();
	if (TextureToUse->loadFromFile(FileName))
	{
		std::cout << "Loaded texture: " << FileName << std::endl;
	}
	else if (!TextureToUse->loadFromFile(FileName))
	{
		std::cout << "Failed to load texture: " << FileName << std::endl;
	}
}

void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom)
{
	SpriteToUse = new sf::Sprite();
	SpriteToUse->setTexture(*TextureToSetFrom);
}
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom, float x, float y)
{
	SpriteToUse = new sf::Sprite();
	SpriteToUse->setTexture(*TextureToSetFrom);
	SpriteToUse->setPosition(x,y);
}
// void CreateSprite(sf::Sprite* &SpriteToUse, Animation* &AnimationToSetFrom)
// {
// 	SpriteToUse = new sf::Sprite();
// 	SpriteToUse = AnimationToSetFrom->GetSprite();
// }
// void CreateSprite(sf::Sprite* &SpriteToUse, Animation* &AnimationToSetFrom, float x, float y)
// {
// 	SpriteToUse = new sf::Sprite();
// 	SpriteToUse = AnimationToSetFrom->GetSprite();
// 	SpriteToUse->setPosition(x,y);
// }
void Clean(sf::Texture* &TextureToDelete)
{
	delete TextureToDelete;
}
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete)
{
	delete SpriteToDelete;
	delete TextureToDelete;
}
// void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete, Animation* &AnimationToDelete)
// {
// 	delete AnimationToDelete;
// 	delete SpriteToDelete;
// 	delete TextureToDelete;
// }
// void Clean(sf::Sprite* & SpriteToDelete, Animation* &AnimationToDelete)
// {
// 	delete AnimationToDelete;
// 	delete SpriteToDelete;
// }