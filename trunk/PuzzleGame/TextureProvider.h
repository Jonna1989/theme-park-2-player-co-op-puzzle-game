#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Load.h"

class TextureProvider
{
public:
	TextureProvider();
	~TextureProvider();
	static TextureProvider* m_instance;
	static TextureProvider* Instance();

	void Initialize();
	void Cleanup();

	void GetSubRect(sf::Vector2i cellPos, sf::Vector2i cellSize, std::string sheetPath, sf::Sprite* sprite);

	sf::Texture* GetTexture(std::string sheetPath);
	std::map<std::string, sf::Texture*> m_textures;

private:
	sf::Sprite* m_sprite;
};

