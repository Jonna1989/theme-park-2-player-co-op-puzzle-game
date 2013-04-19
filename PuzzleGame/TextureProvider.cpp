#include "TextureProvider.h"

#pragma region Base
TextureProvider::TextureProvider()
{
}

TextureProvider::~TextureProvider()
{
	for(std::map<std::string, sf::Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		 delete it->second;
	}
}

#pragma endregion

#pragma region Publics

TextureProvider* TextureProvider::m_instance = 0;

TextureProvider* TextureProvider::Instance()
{
	if(m_instance == 0)
	{
		m_instance = new TextureProvider();
	}

	return m_instance;
}

void TextureProvider::Initialize()
{
	m_sprite = new sf::Sprite();
}

void TextureProvider::Cleanup()
{
	for(std::map<std::string, sf::Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		 delete it->second;
	}
	delete m_sprite;
}

sf::Texture* TextureProvider::GetTexture(std::string sheetPath)
{
	std::map<std::string,  sf::Texture* > ::iterator m_interator = m_textures.find(sheetPath);

	 if(m_interator == m_textures.end())
    {
        sf::Texture* m_texture = new sf::Texture();
		m_texture->loadFromFile(sheetPath);
		
		m_textures.insert(std::pair<std::string,sf::Texture* >(sheetPath,m_texture));
		
        return m_textures.at(sheetPath);
    }
    else
    {
        return m_textures.at(sheetPath);
    }
}

void TextureProvider::GetSubRect(sf::Vector2i cellPos, sf::Vector2i cellSize, std::string sheetPath, sf::Sprite* sprite)
{
	sprite->setTexture(*GetTexture(sheetPath));
	sprite->setTextureRect(sf::IntRect(cellPos.x,cellPos.y,cellSize.x,cellSize.y));
}

#pragma endregion