#include "Load.h"

void LoadTexture(sf::Texture* &TextureToUse, const std::string &FileName)
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
void CreateSprite(sf::Sprite* &SpriteToUse)
{
	SpriteToUse = new sf::Sprite();
}
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom)
{
	CreateSprite(SpriteToUse);
	SpriteToUse->setTexture(*TextureToSetFrom);
}
void CreateSprite(sf::Sprite* &SpriteToUse, sf::Texture* &TextureToSetFrom, float x, float y)
{
	CreateSprite(SpriteToUse,TextureToSetFrom);
	SpriteToUse->setPosition(x,y);
}
void CreateSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture)
{
	CreateSprite(SpriteToUse);
	SpriteToUse->setTexture(*TextureProvider::Instance()->GetTexture(PathToTexture));
}
void CreateSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture, float x, float y)
{
	CreateSprite(SpriteToUse,PathToTexture);
	SpriteToUse->setPosition(x,y);
}
void SetSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture)
{
	SpriteToUse->setTexture(*TextureProvider::Instance()->GetTexture(PathToTexture));
}
void SetSprite(sf::Sprite* &SpriteToUse, const std::string &PathToTexture, float x, float y)
{
	SetSprite(SpriteToUse,PathToTexture);
	SpriteToUse->move(x,y);
}
void Clean(sf::Texture* &TextureToDelete)
{
	delete TextureToDelete;
}
void Clean(sf::Sprite* &SpriteToDelete)
{
	delete SpriteToDelete;
}
void Clean(sf::Texture* &TextureToDelete, sf::Sprite* & SpriteToDelete)
{
	Clean(SpriteToDelete);
	Clean(TextureToDelete);
}
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor)
{
	textToDeclare = new sf::Text();
	textToDeclare->setCharacterSize(charSize);
	textToDeclare->setColor(textColor);
}
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, sf::Vector2f textPosition)
{
	DeclareSfText(textToDeclare,charSize,textColor);
	textToDeclare->setPosition(textPosition);
}
void DeclareSfText(sf::Text* &textToDeclare, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY)
{
	DeclareSfText(textToDeclare,charSize,textColor);
	textToDeclare->setPosition(textPositionX,textPositionY);
}
void DeclareSfText(sf::Text* &textToDeclare, sf::Font* font, unsigned int charSize, const sf::Color textColor, float textPositionX, float textPositionY)
{
	DeclareSfText(textToDeclare,charSize,textColor,textPositionX,textPositionY);
	textToDeclare->setFont(*font);
}
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor)
{
	for (int i = 0; i < NumberOfSfTextsInVector; i++)
	{
		vectorToDeclare.push_back(new sf::Text());
		vectorToDeclare[i]->setCharacterSize(charSize);
		vectorToDeclare[i]->setColor(textColor);
	}
}
void DeclareSfText(std::vector<sf::Text*> &vectorToDeclare, sf::Font* font, int NumberOfSfTextsInVector, unsigned int charSize, const sf::Color textColor)
{
	for (int i = 0; i < NumberOfSfTextsInVector; i++)
	{
		vectorToDeclare.push_back(new sf::Text());
		vectorToDeclare[i]->setFont(*font);
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
	ConvertIntToSfString(intToGetStringFrom,sfStringToUpdateFrom);
	sfTextToConvertTo->setString(sfStringToUpdateFrom);
}
void ConvertIntToSfStringToSfText(int intToGetStringFrom,sf::String &sfStringToUpdateFrom, sf::Text* &sfTextToConvertTo, sf::String addExtraText, bool atEnd)
{
	ConvertIntToSfString(intToGetStringFrom,sfStringToUpdateFrom);
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
std::string ConvertCharToStdString(char charToConvert)
{
	std::stringstream ss;
	std::string s;
	char c = charToConvert;
	ss << c;
	ss >> s;
	return s;
}
char ConvertIntToChar(int intToConvert)
{
	char tempChar = 0;
	tempChar = (char)intToConvert;
	return tempChar;
}
int RandomNumber()
{
	return rand();
}
int RandomNumber(int lowRange, int highRange)
{
	return (rand() % ((highRange-lowRange) - 1) + lowRange +1);
}
unsigned GetNumberOfDigits (unsigned i)
{
	return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}