#include "Load.h"

void LoadTexture(sf::Texture* &TextureToUse, const std::string FileName)
{
	TextureToUse = new sf::Texture();
	if (TextureToUse->loadFromFile(FileName))
	{
		std::cout << "Loaded texture: " << FileName << std::endl;
	}
	else
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

void Clean(sf::Texture* &TextureToDelete)
{
	delete TextureToDelete;
}
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete)
{
	delete SpriteToDelete;
	delete TextureToDelete;
}
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition)
{
	textToDeclare = new sf::Text();
	textToDeclare->setCharacterSize(charSize);
	textToDeclare->setColor(textColor);
	textToDeclare->setPosition(textPosition);
}
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY)
{
	textToDeclare = new sf::Text();
	textToDeclare->setCharacterSize(charSize);
	textToDeclare->setColor(textColor);
	textToDeclare->setPosition(textPositionX,textPositionY);
}
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor)
{
	textToDeclare = new sf::Text();
	textToDeclare->setCharacterSize(charSize);
	textToDeclare->setColor(textColor);
}
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor)
{
	vectorToDeclare.push_back(new sf::Text());
	for (int i = 0; i < NumberOfSfTextsInVector; i++)
	{
		vectorToDeclare[i]->setCharacterSize(charSize);
		vectorToDeclare[i]->setColor(textColor);
	}
}

void ConvertIntToSfString(int intToGetStringFrom,sf::String &sfStringToUpdateFrom)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
}
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd)
{
	std::ostringstream convert;
	convert << intToGetStringFrom;
	std::string tempStdString;
	tempStdString = convert.str();
	sfStringToUpdateFrom = tempStdString;
	if (atEnd == false)
	{
		sfStringToUpdateFrom.insert(0,addExtraText);
	}
	else
	{
		sfStringToUpdateFrom.insert(sfStringToUpdateFrom.getSize(),addExtraText);
	}
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}

std::string ConvertIntToStdString(int intToConvert)
{
	std::ostringstream	s;
	s << intToConvert;
	std::string i_as_string(s.str());
	return i_as_string;
}